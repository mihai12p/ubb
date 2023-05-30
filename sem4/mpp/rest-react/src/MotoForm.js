import React from  'react';
import Motorcycle from './domain/Motorcycle';

class MotoForm extends React.Component
{
    constructor(props)
    {
        super(props);
        this.state = {id: '', brand:'', capacity:''};
    }

    handleIdChange = (event) =>
    {
        this.setState({id: event.target.value});
    }

    handleBrandChange = (event) =>
    {
        this.setState({brand: event.target.value});
    }

    handleCapacityChange = (event) =>
    {
        this.setState({capacity: event.target.value});
    }

    handleAdd = (event) =>
    {
        const motorcycle = new Motorcycle(this.state.id, this.state.brand, this.state.capacity);
        this.props.addFunc(motorcycle);
        event.preventDefault();
    }

    handleUpdate = (event) =>
    {
        const motorcycle = new Motorcycle(this.state.id, this.state.brand, this.state.capacity);
        this.props.updateFunc(motorcycle);
        event.preventDefault();
    }

    render()
    {
        return (
            <React.Fragment>
                <label>
                    ID: <input type="text" value={this.state.id} onChange={this.handleIdChange} />
                </label><br/>
                <label>
                    Brand: <input type="text" value={this.state.brand} onChange={this.handleBrandChange} />
                </label><br/>
                <label>
                    Capacity: <input type="text" value={this.state.capacity} onChange={this.handleCapacityChange} />
                </label><br/><br/>
                <button onClick={this.handleAdd}>Adauga motocicleta</button><br/>
                <button onClick={this.handleUpdate}>Actualizeaza motocicleta</button>
            </React.Fragment>
        );
    }
}

export default MotoForm;