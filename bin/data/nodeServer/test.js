var express = require('express');
var app = express();

//root
app.get('/', function (req, res) {
  res.send('Hello World!');
});

//query for explosion
app.get('/api')

app.listen(3000, function () {
  console.log('Example app listening on port 3000!');
});
