var express = require('express.io'),
	Serial = require('./serial.js'),
	_ = require('lodash')
;


var data = {
	serial: {},
	messages: [],
	moteur: {
		gauche: {vitesse: 0, angle: 180},
		droit: {vitesse: 0, angle: 180}
	}
}

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
	req.io.emit('data', data);
});

app.io.route('message', function(req){

	data.messages.unshift({type: 'instruction', content: req.data.instruction});
	app.io.broadcast('data', data);

	serial.send(req.data.instruction);
});

app.io.route('data', function(req){

	data = _.merge(data, req.data.data);
	app.io.broadcast('data', data);

});

app.io.route('connect', function(req){
	serial.open(req.data.port);
});

app.io.route('close', function(req){
	serial.close();
});

app.io.route('refreshPort', function(req){
	serial.refreshPort();	
});

/*----------------------------

	ARDUINO PART

----------------------------*/

var serial = new Serial();

serial.on('message', function(message){
	// app.io.broadcast('message', message);
	data.messages.unshift(message);
	app.io.broadcast('data', data);
})

serial.on('ports', function(){
	data.serial = serial.introduceYourself();
	app.io.broadcast('data', data);
})

serial.on('open', function(err, port){
	if(err){
		data.messages.unshift({type: 'error', content: "Erreur lors de la connection: " + err});
	}
	else {
		data.messages.unshift({type: 'success', content: "Connection ouverte avec " + port});
		data.serial = serial.introduceYourself();
	}

	app.io.broadcast('data', data);
});

serial.on('closed', function(){
	data.serial = serial.introduceYourself();
	data.messages = [{type:"message", content: "Connection fermée"}];

	app.io.broadcast('data', data);	
})

app.listen(8080);
serial.open("/dev/cu.usbmodemfa131");
