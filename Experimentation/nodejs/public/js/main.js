var app = angular.module('app', []);
var io = io.connect() ;

app

.controller('MainController', ['$scope', function($scope){

	io.emit('ready');

	$scope.moteur = {
		vitesse: 0,
		sens: 0,
		k: 0.053591,
		intensite: 0.33,
		resistance: 1.8,
		bloque: 0,
		tension_max: 12
	};



	io.on('data', function(data){

		//console.log(JSON.stringify(data));
		$scope.data = data ;
		$scope.flash = "" ;
		$scope.$apply();
	});


	$scope.clearUntil = 0 ;

	$scope.maxVitesse = function(){
		$scope.moteur.vitesse_max = parseInt(($scope.moteur.tension_max / $scope.moteur.k - $scope.moteur.resistance * $scope.moteur.intensite * $scope.moteur.k) * 30 / Math.PI) ;//En tour/minute
	};
	$scope.maxVitesse();

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

	$scope.setMotor = function(){
		
		console.log($scope.moteur.vitesse, $scope.moteur.vitesse_max);
		var order = parseInt($scope.moteur.vitesse / $scope.moteur.vitesse_max * 255) ;
		order += ';' ;

		order += $scope.moteur.sens ;
		order += ';' ;

		order += $scope.moteur.bloque == 1 ? 1 : 0 ;
		order += ';' ;

		$scope.order = order ;

		$scope.sendData();
		$scope.sendOrder();
	}

	$scope.bloque = function(){
		$scope.moteur.bloque = 1 ;
		$scope.setMotor();
		$scope.moteur.bloque = 0 ;
	}

	$scope.changeSens = function(){
		$scope.moteur.sens = ($scope.moteur.sens + 1) % 2 ;
		$scope.setMotor();
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

.filter('numberFixedLen', function () {
	return function (n, len) {
		var num = parseInt(n, 10);
		len = parseInt(len, 10);
		if (isNaN(num) || isNaN(len)) {
			return n;
		}
		num = ''+num;
		while (num.length < len) {
			num = '0'+num;
		}
		return num;
	};
});

;