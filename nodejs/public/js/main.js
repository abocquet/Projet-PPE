var app = angular.module('app', []);
var io = io.connect() ;

app

.controller('MainController', ['$scope', function($scope){

	io.emit('ready');

	io.on('message', function(stack){
		$scope.stack = stack ;
		$scope.$apply();
	});

	$scope.sendOrder = function(){

		if($scope.order.trim().length > 0)
		{
			io.emit('order', {instruction: $scope.order});
			$scope.order = "";
		}

		return false; 

	};

	$scope.alertType = function(message){

		var className = 'alert alert-';

		switch(message.type){
			case "data": 
				className += "info";
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