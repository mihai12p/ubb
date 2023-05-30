import React from 'react';
import findAll from './api/findAll';
import create from './api/create';
import update from './api/update';
import remove from './api/remove';
import MotoForm from './MotoForm';
import MotoTable from './MotoTable';

class App extends React.Component
{
    constructor(props)
	{
        super(props);
        this.state = 
		{
			motorcycles:  [],
            addFunc: this.addFunc.bind(this),
			deleteFunc: this.deleteFunc.bind(this),
			updateFunc: this.updateFunc.bind(this),
        }
    }

	addFunc(motorcycle)
	{
        create(motorcycle)
			.then(_ => findAll())
            .then(motorcycles => this.setState({motorcycles}))
            .catch(error => console.log('create has failed ', error));
    }

	updateFunc(motorcycle)
	{
        update(motorcycle, motorcycle.id)
            .then(_ => findAll())
            .then(motorcycles=>this.setState({motorcycles}))
            .catch(error => console.log('update has failed ', error));
    }

	deleteFunc(motorcycle)
	{
        remove(motorcycle.id)
            .then(_ => findAll())
            .then(motorcycles=>this.setState({motorcycles}))
			.catch(error => console.log('delete has failed ', error));
    }

	componentDidMount()
	{
        findAll().then(motorcycles => this.setState({motorcycles}));
    }

    render()
	{
        return (
			<div className="MotorcycleApp">
				<h1>MotoGP</h1>
				<MotoForm addFunc={this.state.addFunc} updateFunc={this.state.updateFunc}/><br/><br/>
				<MotoTable motorcycles={this.state.motorcycles} deleteFunc={this.state.deleteFunc}/>
			</div>
        );
    }
}

export default App;