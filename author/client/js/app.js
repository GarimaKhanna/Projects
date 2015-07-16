'use strict';

angular
  .module('app', [
    'lbServices',
    'ui.router',
	'services'
  ])
  .config(['$stateProvider', '$urlRouterProvider', function($stateProvider,
      $urlRouterProvider) {
    $stateProvider
      .state('book', {
        url: '/book',
        templateUrl: 'js/book/templates/book.html',
        controller: 'BookCtrl',
      })
	  .state('login', {
        url: '/login',
        templateUrl: 'js/login/templates/login.html',
        controller: 'LoginCtrl',
      });
    $urlRouterProvider.otherwise('login');
  }]);
