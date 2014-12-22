var EventEmitter = require('events').EventEmitter,
	util = require('util')
;

var serialport = require("serialport") ;
var Connection = serialport.SerialPort ;

var Serial = function(){
	EventEmitter.call(this);

	this.ports = [] ;
	this.port = '' ;
	var self = this ;

	this.refreshPort();

}

util.inherits(Serial, EventEmitter);

Serial.prototype.refreshPort = function(){

	var self = this ;

	self.ports = [];

	serialport.list(function (err, ports) {

		ports.forEach(function(port) {
			self.ports.push(port.comName);
		});

		self.emit('ports');

	});
}

Serial.prototype.open = function(port){

	var self = this ;

	var bridge = new Connection(port, {
		baudrate: 9600,
		parser: serialport.parsers.readline("\n")
	}, false);


	bridge.open(function (err) {

		if(err){
			self.emit('open', err, port);
		}
		else {

			self.port = port ;
			bridge.on('data', function(data) {
				self.emit('message', {type: 'data', content: data});
			});

			self.send = function(message){

				bridge.write(message + '\n', function(err, results) {
					if (err) {
						self.emit('message', {type: 'error', content: "Erreur de transfert: " + err});
					}
				});

			};

			self.close = function(){
				console.log("closing");
				bridge.close(function(err){
					if(err){
						console.log("Error on close:", err);
					}	
					else {
						self.port = '' ;
						self.emit('closed');

						self.send = undefined ;
						self.close = undefined ;
					} 
				});
			}
			
			self.emit('open', err, port);
		}
		
	});
}


Serial.prototype.introduceYourself = function(){

	return {

		ports: this.ports,
		isConnected: this.port.length > 0,
		port: this.port 

	}

}


module.exports = Serial;