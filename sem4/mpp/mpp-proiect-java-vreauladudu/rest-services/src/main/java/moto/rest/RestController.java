package moto.rest;

import moto.Motorcycle;
import moto.repository.MotorcycleRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

@org.springframework.web.bind.annotation.RestController
@RequestMapping("/moto/motorcycles")
public class RestController
{
    @Autowired
    private MotorcycleRepository motorcycles;

    @RequestMapping(method = RequestMethod.GET)
    public Iterable<Motorcycle> findAll()
    {
        System.out.println("Find all motorcycles...");
        return this.motorcycles.findAll();
    }

    @RequestMapping(value = "/{id}", method = RequestMethod.GET)
    public ResponseEntity<?> find(@PathVariable Integer id)
    {
        System.out.println("Find one motorcycle by id " + id + "...");
        Motorcycle motorcycle = this.motorcycles.find(id);
        if (motorcycle == null)
        {
            return new ResponseEntity<>("Motorcycle not found", HttpStatus.NOT_FOUND);
        }

        return new ResponseEntity<>(motorcycle, HttpStatus.OK);
    }

    @RequestMapping(method = RequestMethod.POST)
    public Motorcycle save(@RequestBody Motorcycle motorcycle)
    {
        System.out.println("Save motorcycle " + motorcycle + "...");
        Integer maximumId = 0;
        Iterable<Motorcycle> motorcycleList = this.motorcycles.findAll();
        for (Motorcycle m : motorcycleList)
        {
            if (m.getId() > maximumId)
            {
                maximumId = m.getId();
            }
        }
        motorcycle.setId(maximumId + 1);
        return this.motorcycles.save(motorcycle);
    }

    @RequestMapping(value = "/{id}", method = RequestMethod.PUT)
    public Motorcycle update(@RequestBody Motorcycle motorcycle, @PathVariable Integer id)
    {
        motorcycle.setId(id);
        System.out.println("Update motorcycle " + motorcycle + "...");
        return this.motorcycles.update(motorcycle);
    }

    @RequestMapping(value = "/{id}", method = RequestMethod.DELETE)
    public ResponseEntity<?> remove(@PathVariable Integer id)
    {
        System.out.println("Remove motorcycle with id " + id + "...");
        return new ResponseEntity<>(this.motorcycles.remove(id), HttpStatus.OK);
    }
}