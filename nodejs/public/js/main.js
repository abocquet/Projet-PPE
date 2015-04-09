var app = angular.module('app', []);
var io = io.connect() ;

app

.controller('MainController', ['$scope', function($scope){

	io.emit('ready');

	$scope.moteur = {
		vitesse: 0,
		sens: 0
	};

	io.on('data', function(data){

		console.log(JSON.stringify(data));
		$scope.data = data ;
		$scope.flash = "" ;
		$scope.$apply();
	});


	$scope.clearUntil = 0 ;

	$scope.sendOrder = function(){

		if($scope.order.trim().length > 0)
		{
			io.emit('message', {instruction: $scope.order});
			$scope.order = "";
		}

		return false; 

	};

	$scope.sendData = function(){
		io.emit('data', {data: $scope.data});
	}

	$scope.setMotors = function(){

		var order = "motors:";

		order += $scope.data.moteur.vitesse ;
		order += ';' ;

		order += $scope.data.moteur.sens ;
		order += ';' ;

		$scope.order = order ;

		$scope.sendData();
		$scope.sendOrder();
	}

	$scope.connect = function(){
		if($scope.port){
			io.emit('connect', {port: $scope.port});
		}
	};

	$scope.close = function(){
		io.emit('close');
	}

	$scope.refreshPort = function(){
		if($scope.flash.length == 0){
			$scope.flash = "Rafraichissment des ports en cours" ;
			io.emit('refreshPort');		
		}
	}

	$scope.clearStack = function(){
		$scope.clearUntil = $scope.data.messages.length ;
	}

	$scope.alertType = function(message){

		var className = 'alert alert-';

		switch(message.type){
			case "data": 
				className += "info";
				break ;
			case "success": 
				className += "success";
				break ;
			case "instruction":
				className += "warning";
				break ;
			case "error":
				className += "danger";
				break ;
			default:
				className += "info";
				break ;
		}

		return className ;

	}

}])


;