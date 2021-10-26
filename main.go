package main

import (
       "os"
       "log"
       "net/http"
       "github.com/gin-gonic/contrib/static"
       "github.com/gin-gonic/gin"
       "os/exec"
)

func main() {
     port := os.Getenv("PORT")

     if port == "" {
     	log.Fatal("$PORT must be set")
     }

     router := gin.Default()
     router.Use(gin.Logger())
     router.Use(static.Serve("/", static.LocalFile("web/puzzle-frontend/build/.", true)))

     router.GET("/input/query", func(c *gin.Context) {
     			   c.Header("Content-Type", "application/json")
			   inputState := c.DefaultQuery("inputState", "null")
			   goalState := c.Query("goalState")
			   algorithm := c.Query("algo")
			   depth := c.Query("depth")
			   program := "./eight_puzzle"
			   flag := "nf"
			   eightPuzzle := exec.Command(program, flag, algorithm, inputState, goalState, depth)
			   stdout, err := eightPuzzle.Output()

			   if err != nil {
			       c.JSON(http.StatusOK, err.Error())
			       return
			   }

     			   //c.JSON(http.StatusOK, "inputState: " + inputState + " goalState: " + goalState + " algorithm: " + algorithm + " depth: " + depth);
			   c.JSON(http.StatusOK, string(stdout))
     })

     router.Run(":" + port)
}