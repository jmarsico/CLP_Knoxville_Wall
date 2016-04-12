//Lets require/import the HTTP module
var http = require('http');
var osc = require('osc-min');
var udp = require('dgram');
var app = require('express');


//udp setup
udp = udp.createSocket("udp4");

app = express();

// app.setStatic('resources');

var get_explode_params = function(req, cb) {
  var x = parseInt(req.param('x'));
  var y = parseInt(req.param('y'));
  var size = parseInt(req.param('size'));
  if (x>=0 && y>=0 && size>=0) {
    cb(null, x, y, size);
  } else {
    cb("missing parameters");
  }
}



app.get('/api/explode/:x/:y/:size', function(req, res) {
  get_color_params(req, function(err, x, y, size) {
    if (err) {
      res.json({
        'status': 'fail',
        msg: err
      });
    } else {
      for (var i = 0; i < button_color_states12.length; i++) {
        set_button_color_state(i, 8, r, g, b);
      }
      socks.emit('update', button_colors_to_array());
      res.json({
        'status': 'success'
      })
    }
  });
});

//explode message
dispatcher.onGet("/explode", function(req, res){

	var x;
	x = req.

	res.writeHead(200, {'Content-Type': 'text/plain'});

	//send an OSC message
	var buf;
	buf = osc.toBuffer({
		address: "/explode",
		args: [
		12,
		12.3,
		90,
		]
	});
	udp.send(buf, 0, buf.length, 12345, "localhost");

	res.end('Page One');
});

dispatcher.onPost("/post1", function(req, res) {
	res.writeHead(200, {'Content-Type': 'text/plain'});
	res.end('Got Post Data');
});

//Lets define a port we want to listen to
const PORT=8080;

//We need a function which handles requests and send response
function handleRequest(request, response){

	try{
		console.log(request.url);
		dispatcher.dispatch(request, response);
	} catch(err) {
		console.log(err);
	}
}



//Create a server
var server = http.createServer(handleRequest);

//Lets start our server
server.listen(PORT, function(){
    //Callback triggered when server is successfully listening. Hurray!
    console.log("Server listening on: http://localhost:%s", PORT);
});
