import React, { Component } from  'react';
import Box from '@mui/material/Box';
import Paper from '@mui/material/Paper';
import Stack from '@mui/material/Stack';
import TextField from '@mui/material/TextField';
import Select from '@mui/material/Select';
import MenuItem from '@mui/material/MenuItem';
import InputLabel from '@mui/material/InputLabel';
import FormControl from '@mui/material/FormControl';
import Button from '@mui/material/Button';
import Slider from '@mui/material/Slider';
import EightPuzzle from './eight_puzzle.js';

class RequiredPuzzleData extends Component {
    constructor(props) {
	super(props);
	this.state = {initial: '', goal: '', algo: '', depth: 1, dataLoaded: false, puzzleSolution: []};

	this.handleChange = this.handleChange.bind(this);
	this.handleSubmit = this.handleSubmit.bind(this);
	this.handleReset = this.handleReset.bind(this);
    }

    handleChange(event) {
	this.setState({[event.target.name]: event.target.value});
    }

    handleSubmit(event) {
	this.setState({dataLoaded: true});
	fetch('/input/query?inputState=' + this.state.initial.split(" ").join("") + '&goalState=' + this.state.goal.split(" ").join("") + '&algo=' + this.state.algo + '&depth=' + this.state.depth)
	    .then(response => response.json())
	    .then(data => this.setState({ puzzleSolution: (JSON.parse(data)).moves }));
	event.preventDefault();
    }
    
    handleReset(event) {
	this.setState({
	    initial: '',
	    goal: '',
	    algo: '',
	    depth: 1,
	    dataLoaded: false,
	    puzzleSolution: []
	});
    }
    
    render() {
	const format = "Enter the game state, from top-left to right-bottom, 9 characters with a space between them, e.g. '* 1 2 3 4 5 6 7 8'";

	let loadPuzzleStates;
	let loadSolution;
	
	if(this.state.dataLoaded) {
	    loadPuzzleStates = (
		<Paper elevation={0} square={true} variant="outlined" sx={{ height: '49.6vh' }}>
		    <Stack spacing={2} justifyContent="space-evenly" direction="row">
		        <Stack spacing={4} justifyContent="space-evenly" alignItems="center">
		            <h1>Initial Puzzle State</h1>
		            <EightPuzzle str={this.state.initial}/>
		        </Stack>
		        <Stack spacing={4} justifyContent="space-evenly" alignItems="center">
		            <h1>Final Puzzle State</h1>
		            <EightPuzzle str={this.state.goal}/>
		        </Stack>
		    </Stack>
		</Paper>
	    );

	    var solutions;

	    solutions = this.state.puzzleSolution.map(function(element, index) {
		if(element.length != 17) {
		    return <h4>{element}</h4>;
		}
		else {
		    return (
			    <>
			    <h4>Move {index}</h4>
			    <EightPuzzle str={element}/>
			    </>
		    );
		}
	    }.bind(this));
	    
	    loadSolution = (
		    <Paper elevation={0} square={true} sx={{ minHeight: '45vh' }}>
		    <Stack spacing={2} justifyContent="space-evenly" alignItems="center">
		        <h1>Solution</h1>
		        {solutions}
		    </Stack>
		</Paper>
	    );
	} else {
	    loadPuzzleStates = null;
	    loadSolution = null;
	}
	
	return (
	    <Box display="grid" gridTemplateColumns="repeat(12, 1fr)" sx={{ backgroundColor: '#121212', height: '94.9vh' }}>
		<Box gridColumn="span 5">
		    <Paper elevation={0} square={true} variant="outlined">
		        <Stack justifyContent="space-evenly" alignItems="stretch" spacing={2}>
		            <h1>Puzzle Input</h1>
		            <Box component="form" noValidate mt={2} onSubmit={this.handleSubmit}>
		                <Stack justifyContent="space-evenly" alignItems="center" spacing={2}>
		                    <Stack spacing={2} direction="row">
		                        <h4>Initial State:</h4>
                                        <TextField name="initial" variant="standard" label="Initial" type="text" size="small" required="true" id="initialState" placeholder="Initial Puzzle State" helperText={format} value={this.state.initial} onChange={this.handleChange}/>
	                            </Stack>
		                    <Stack spacing={2} direction="row">
		                        <h4>Goal State:</h4>
		                        <TextField name="goal" variant="standard" label="Goal" type="text" size="small" required="true" id="goalState" placeholder="Goal Puzzle State" helperText={format} value={this.state.goal} onChange={this.handleChange}/>
	                            </Stack>
		                    <Stack spacing={2} direction="row">
		                        <h4>Search Algorithm:</h4>
		                        <FormControl variant="standard" sx={{ m: 1, minWidth: 120 }}>
                                            <InputLabel id="algo-label">Algorithm</InputLabel>
		                            <Select name="algo" value={this.state.algo} onChange={this.handleChange} label="Algorithm" label-id="algo-label" autoWidth>
		                                <MenuItem value={'dfs'}>Depth-First Search</MenuItem>
		                                <MenuItem value={'ids'}>Iterative-Deepening Search</MenuItem>
		                                <MenuItem value={'astar1'}>A* Search (Misplaced Tiles Heuristic)</MenuItem>
		                                <MenuItem value={'astar2'}>A* Search (Manhattan Heuristic)</MenuItem>
	                                    </Select>
		                        </FormControl>
		                    </Stack>
		                    <Stack spacing={2} direction="row" sx={{ mb: 1 }} alignItems="center" justifyContent="space-evenly">
		                        <h4>Depth Limit:</h4>
		                        <Box>
		                            <Slider aria-label="Default" name="depth" value={this.state.depth} onChange={this.handleChange} valueLabelDisplay="auto" min={1} sx={{ width: '50vh'}}/>
	                                </Box>
	                            </Stack>
		                    <Stack spacing={2} direction="row" sx={{ mb: 1 }} alignItems="center">
		                        <Button color="secondary" type="submit">Search</Button>
		                        <Button color="secondary" type="reset" onClick={this.handleReset}>Reset</Button>
		                    </Stack>
		                </Stack>
	                    </Box>
		        </Stack>
		    </Paper>
	        </Box>
		<Box gridColumn="span 7">
		    {loadPuzzleStates}
	        </Box>
		<Box gridColumn="span 12">
		    {loadSolution}
	        </Box>
	    </Box>
	)
    }
}

export default RequiredPuzzleData;
