//Lets require/import the HTTP module
var http = require('http');
var osc = require('osc-min');
var udp = require('dgram');
var express = require('express');
var bodyParser = require('body-parser');

//http://localhost:8080/api?explode=2%201&force=0.23%200.1&sweep=0.1%200.2%200.4%200.2%200.3&dots=0.1%200.2

var app = express();
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({extended: false}));


var systemStatus = 'running';

//udp setup
udp = udp.createSocket("udp4");

//EXPLODE!!
function send_explode_message(explodeParams) {
    var params = explodeParams.split(' ');


    if(params.length >= 2){
        var buf;            //the UDP buffer
        //if we only receive 2 parameters, default size param to 0.5
        if(params.length == 2){
            buf = osc.toBuffer({
                address: "/explode",
                args: [
                    params[0],
                    params[1],
                    0.5
                ]
            })
        }
        //if we receive all 3 parameters for explode
        else if(params.length == 3){
            buf = osc.toBuffer({
                address: "/explode",
                args: [
                    params[0],
                    params[1],
                    params[2]
                ]
            })
        }
        udp.send(buf, 0, buf.length, 12345, "localhost");
    }
}


function send_sweep_params(sweepParams) {
    //?sweep=x1 y1 x2 y2 speed
    var params = sweepParams.split(' ');


    if(params.length == 5){
        var buf;
        buf = osc.toBuffer({
            address: "/sweep",
            args: [
                params[0],
                params[1],
                params[2],
                params[3],
                params[4]
            ]
        })
        udp.send(buf, 0, buf.length, 12345, "localhost");
    }
}

function send_force_params(forceParams) {
    var params = forceParams.split(' ');
    if(params.length == 2){
        var buf;
        buf = osc.toBuffer({
            address: '/force',
            args: [
                params[0],
                params[1]
            ]
        })
        udp.send(buf, 0, buf.length, 12345, "localhost");
    }
}

function send_dots_params(dotsParams){
    var params = dotsParams.split(' ');
    if(params.length == 2){
        var buf;
        buf = osc.toBuffer({
            address: '/dots',
            args: [
                params[0],
                params[1]
            ]
        })
        udp.send(buf, 0, buf.length, 12345, "localhost");
    }

}

app.get('/api', function(req, res){
    //explode
    if(req.query.explode !== 'undefined' && req.query.explode){
        send_explode_message(req.query.explode);
    }
    //force (gravity)
    if(req.query.force !== 'undefined' && req.query.force){
        send_force_params(req.query.force);
    }
    //sweep
    if(req.query.sweep !== 'undefined' && req.query.sweep){
        send_sweep_params(req.query.sweep);
    }
    //dots
    if(req.query.dots !== 'undefined' && req.query.dots){
        send_dots_params(req.query.dots);
    }

    res.json({
        'explode': req.query.explode,
        'force': req.query.force,
        'sweep': req.query.sweep,
        'dots': req.query.dots
    })
});


app.get('/admin', function(req,res){
    if(req.query.system){
        
    }
    res.json({
        'status': systemStatus
    })
});



app.get('/', function(req,res){
    res.send('Hello World!');
});

//Lets define a port we want to listen to
const PORT=8080;

//Lets start our server
app.listen(PORT, function(){
    //Callback triggered when server is successfully listening. Hurray!
    console.log("Server listening on: http://localhost:%s", PORT);
});
