import React from  'react';
import './Moto.css'

class MotoRow extends React.Component
{
    handleRemove = (_) =>
    {
        this.props.deleteFunc(this.props.motorcycle);
    }

    render()
    {
        return (
            <tr>
                <td>{this.props.motorcycle.id}</td>
                <td>{this.props.motorcycle.brand}</td>
                <td>{this.props.motorcycle.capacity}</td>
                <td><button onClick={this.handleRemove}>Sterge</button></td>
            </tr>
        );
    }
}

class MotoTable extends React.Component
{
    render()
    {
        const rows = [];
        this.props.motorcycles.forEach(function(motorcycle)
        {
            rows.push(<MotoRow motorcycle={motorcycle} key={motorcycle.id} deleteFunc={this.props.deleteFunc} />);
        }.bind(this));

        return (
            <table className="center">
                <thead>
                <tr>
                    <th>Id</th>
                    <th>Brand</th>
                    <th>Capacity</th>
                    <th></th>
                </tr>
                </thead>
                <tbody>{rows}</tbody>
            </table>
        );
    }
}

export default MotoTable;