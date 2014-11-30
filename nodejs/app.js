var express = require('express.io'),
	Arduino = require('./arduino.js'),
	_ = require('lodash')
;


var stack = [{type:"message", content: "Hi there !"}];

/*----------------------------

	SERVER PART

----------------------------*/


var app = require('express.io')()
app.http().io();
app.use(express.static(__dirname + "/public"));

app.get('/', function(req, res){ res.sendFile('/public/index.html'); });

/*----------------------------

	BRIDGE PART

----------------------------*/

app.io.route('ready', function(req){
	req.io.emit('message', stack);
});

app.io.route('order', function(req){

	// req.io.broadcast('new-instruction', req.data.instruction);
	stack.unshift({type: 'instruction', content:  req.data.instruction})
	app.io.broadcast('message', stack);

	arduino.send(req.data.instruction);

});

/*----------------------------

	ARDUINO PART

----------------------------*/

var arduino = new Arduino();

arduino.on('message', function(message){
	// app.io.broadcast('message', message);
	stack.unshift(message);
	app.io.broadcast('message', stack);
})

app.listen(8000);
arduino.open("/dev/tty.usbmodemfd121");