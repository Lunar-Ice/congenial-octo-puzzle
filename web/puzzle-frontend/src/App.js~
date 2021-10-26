import './App.css';
import React from 'react';
import EightPuzzle from './eight_puzzle.js';
import Box from '@mui/material/Box';
import Paper from '@mui/material/Paper';
import Toolbar from '@mui/material/Toolbar';
import AppBar from '@mui/material/AppBar';
import Typography from '@mui/material/Typography';
import RequiredPuzzleData from './form.js';
import { createTheme, ThemeProvider } from '@mui/material/styles'

function App() {
    const theme = createTheme({
	palette: {
	    mode: "dark",
	    primary: {
		main: '#009edc',
	    },
	    secondary: {
		main: '#dc3e00',
	    },
	    background: {
		paper: '#080705',
		default: '#121212',
	    },
	    text: {
		primary: '#dc3e00',
	    },
	},
    });
    return (
	<div className="App">
	    <ThemeProvider theme={theme}>
	        <AppBar position="static">
	            <Toolbar variant="dense">
	                <Typography variant="h6">Eight-Puzzle Solver</Typography>
	            </Toolbar>
	        </AppBar>
	        <RequiredPuzzleData/>
	    </ThemeProvider>
	</div>
    );
}

export default App;
