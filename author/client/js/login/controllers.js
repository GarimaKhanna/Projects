'use strict';

angular
  .module('app')
  .controller('LoginCtrl', function($scope, $window, LoginService, $state) {
    $scope.data = {};
 
    $scope.login = function() {
        LoginService.loginUser($scope.data.username, $scope.data.password).success(function(data) {
            $state.go('book');
        }).error(function(data) {
			$window.alert("Invalid login");
           console.log("Invalid login");
        });
    }
})
