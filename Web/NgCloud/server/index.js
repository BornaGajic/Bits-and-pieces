const express = require("express");
const MongoClient = require("mongodb").MongoClient;
const { ObjectId } = require("mongodb");
const { json } = require("express");

const port = 3000 || process.env.PORT;

const app =  express();
app.use(express.json());

const route = '/api/files';

const url = "mongodb://localhost:27017";
const dbName = "examples";

(async () => {

    let client, db;
    try
    {
        client = await MongoClient.connect(url, { useUnifiedTopology: true });
        db = client.db(dbName);
    }
    catch (e)
    {
        console.log(e);
    }
    
    let collection = db.collection("files");

    app.post(route, async (req, res) => {
        const body = req.body;
        const fileMetadata = {...body};
        
        fileMetadata["_id"] = new ObjectId();
        
        collection.insertOne(fileMetadata);
    
        res.status(201).send(fileMetadata);
    });
      
    app.get(route, async (req, res) => {
        let itemsPerPage = parseInt(req.query["itemsPerPage"]);
        let currentPage = parseInt(req.query["currentPage"]);
        
        let numberOfDocuments = await collection.find().count();
        let cursor = collection.find().skip(itemsPerPage * (currentPage - 1)).limit(itemsPerPage);

        const result = await cursor.toArray();

        res.send({ totalItems: numberOfDocuments, files: result });
    });

    // get next document
    app.get(`${route}/nextDocument`, async (req, res) => {
        let itemsPerPage = parseInt(req.query["itemsPerPage"]);
        let currentPage = parseInt(req.query["currentPage"]);

        let nextDocument = collection.find().skip((itemsPerPage * currentPage) + itemsPerPage - 1).limit(1);
        let result = (await nextDocument.toArray()).slice(-1)[0];

        result != undefined ? res.send({nextDocument: result }) : res.send({nextDocument: null});
    });
    
  
    app.delete(`${route}/:id`, async (req, res)=> {
        const id = new ObjectId(req.params.id);
        
        await collection.deleteOne({ "_id": id })

        res.send();
    });
    
    app.listen(port, async () => {
        console.log(`Listening on ${port}`);
    });
})();