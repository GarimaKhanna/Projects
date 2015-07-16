'use strict';

angular
  .module('app')
  .controller('BookCtrl', ['$scope', '$state', 'Book', function($scope, $state,
      Book) {
    $scope.books = [];
	
	$scope.orderProp = 'name';
    $scope.direction = false;
    
    $scope.sort = function(column) {
      if ($scope.orderProp === column) {
        $scope.direction = !$scope.direction;
      } else {
        $scope.orderProp = column;
        $scope.direction = false;
      }
    }
	
	
	console.log("hello")
    function getBooks() {
      Book
        .find()
        .$promise
        .then(function(results) {
          $scope.books = results;
        });
		console.log("hello2")
    }
    getBooks();

    $scope.addBook = function() {
		console.log("hello-inside addbook");
      Book
        .create($scope.newBook)
        .$promise
        .then(function(book) {
          $scope.newBook = '';
          $scope.bookForm.name.$setPristine();
          $scope.bookForm.price.$setPristine();
          $scope.bookForm.releaseDate.$setPristine();
          $('.focus').focus();
          getBooks();
		  console.log("hello3")
        });
    };

    $scope.removeBook = function(item) {
      Book
        .deleteById(item)
        .$promise
        .then(function() {
          getBooks();
		  console.log("hello4")
        });
    };
  }]);
