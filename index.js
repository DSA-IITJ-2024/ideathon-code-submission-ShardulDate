const express = require('express');
const path = require('path');
const formHandler = require('./formHandler');
const app = express();

app.use(express.static(__dirname));

app.use('/', formHandler);

app.get('/', (req, res) => {
    res.sendFile(path.join(__dirname, 'index.html'));
});

app.listen(3000, () => {
    console.log('Server is running on port 3000');
});