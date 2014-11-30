var EventEmitter = require('events').EventEmitter,
	util = require('util')
;

var serialport = require("serialport") ;
var Connection = serialport.SerialPort ;

// serialport.list(function (err, ports) {
//   ports.forEach(function(port) {
//     console.log(port.comName);
//     console.log(port.pnpId);
//     console.log(port.manufacturer);
//   });
// });

var Arduino = function(){
	EventEmitter.call(this);
}

util.inherits(Arduino, EventEmitter);

Arduino.prototype.open = function(port){

	var self = this ;

	var bridge = new Connection(port, {
		baudrate: 9600,
		parser: serialport.parsers.readline("\n")
	}, false);


	bridge.open(function (error) {
		if (error) {
			self.emit('message', {type: 'error', content: error.toString()});
		} else {

			bridge.on('data', function(data) {
				self.emit('message', {type: 'data', content: data});
			});

			self.send = function(message){

				bridge.write(message, function(err, results) {
					if (err) {
						self.emit('message', {type: 'error', content: err});
					}
				});

			};
		}
	});
}


module.exports = Arduino;