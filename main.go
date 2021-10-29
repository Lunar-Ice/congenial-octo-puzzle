package main

import (
       "os"
       "log"
       "net/http"
       "github.com/gin-gonic/contrib/static"
       "github.com/gin-gonic/gin"
       "os/exec"
       "database/sql"
       "github.com/lib/pq"
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
			   dbURL := os.Getenv("DATABASE_URL")

     			   connection, _ := pq.ParseURL(dbURL)
     			   connection += " sslmode=require"

			   db, e := sql.Open("postgres", connection)

			   if e != nil {
			      panic(e)
			   }

			   searchStatement := `SELECT solution from eightpuzzledata WHERE "inputState"=$1 AND "goalState"=$2 AND algorithm=$3 AND "depthLimit"=$4;` 

			   solution := db.QueryRow(searchStatement, inputState, goalState, algorithm, depth);

			   if solution != nil {
			      c.JSON(http.StatusOK, solution)
			      return
			   }

			   eightPuzzle := exec.Command(program, flag, algorithm, inputState, goalState, depth)
			   stdout, err := eightPuzzle.Output()

			   if err != nil {
			       c.JSON(http.StatusOK, err.Error())
			       return
			   }

			   sqlStatement := `
			   INSERT INTO eightpuzzledata ("inputState", "goalState", algorithm, "depthLimit", solution)
			   VALUES ($1, $2, $3, $4, $5)
			   RETURNING id`

			   id := 0
			   dberr := db.QueryRow(sqlStatement, inputState, goalState, algorithm, depth, string(stdout)).Scan(&id)

			   if dberr != nil {
			      panic(dberr)
			   }

			   c.JSON(http.StatusOK, string(stdout))
     })

     router.Run(":" + port)
}