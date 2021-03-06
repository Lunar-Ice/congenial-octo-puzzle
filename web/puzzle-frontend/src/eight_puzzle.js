import React, { Component } from 'react';
import Table from '@mui/material/Table';
import TableBody from '@mui/material/TableBody';
import TableCell from '@mui/material/TableCell';
import TableRow from '@mui/material/TableRow';
import Paper from '@mui/material/Paper';
import TableContainer from '@mui/material/TableContainer';

class EightPuzzle extends Component {
    constructor(props) {
	super(props);
	this.state = {str: props.str};

	this.handleChange = this.handleChange.bind(this);
    }

    handleChange(event) {
	this.setState({str: event.target.value});
    }
    
    render() {
	var arr = this.props.str.split(" ");
	var temp = "";
	var eightPuzzle = [];
	var count = 0;
	for(var i = 1; i <= arr.length; i++) {
	    temp += arr[i-1];
	    if(i % 3 === 0) {
		var t = temp.split("");
		eightPuzzle.push(<TableRow key={"tr" + count}>{t.map((rc, x) => (rc !== "*") ? <TableCell sx={{ borderBottom:'none', borderRadius:4, boxShadow:1, bgcolor: 'background.paper', fontSize: '20pt', fontWeight: "bold" }} align="center" variant="outlined" spacing={0.5} key={"td" + x}>{rc}</TableCell>: <TableCell sx={{ borderBottom:'none', borderRadius:4 }}></TableCell>)}</TableRow>); 
		count++;
		temp = "";
	    }
	}
	
	return (
       	    <Paper key={this.state.str} elevation={0} square={true}>
		<Table size="small" sx={{ height:250, width:250, border:4, bgcolor: 'white' }}>
		    <TableBody>
		        {eightPuzzle}
		    </TableBody>
		</Table>
	    </Paper>
	);
    }
}

export default EightPuzzle;
