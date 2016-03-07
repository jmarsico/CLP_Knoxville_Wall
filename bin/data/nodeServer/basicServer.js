//Lets require/import the HTTP module
var http = require('http');
var osc = require('osc-min');
var udp = require('dgram');
var dispatcher = require('httpdispatcher');


//udp setup
udp = udp.createSocket("udp4");

dispatcher.setStatic('resources');

dispatcher.onGet("/page1", function(req, res){
	res.writeHead(200, {'Content-Type': 'text/plain'});

	//send an OSC message
	var buf;
	buf = osc.toBuffer({
		address: "/test",
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