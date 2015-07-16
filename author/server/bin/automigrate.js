var path = require('path');
var app = require(path.resolve(__dirname, '../server'));

var books = [
  {
    name: 'Book1',
    price: 1000,
    releaseDate: new Date()
  }
];
var dataSource = app.dataSources.accountDs;

dataSource.automigrate('Book', function(err) {
  if (err) console.log(err);

  var Book = app.models.Book;
  var count = books.length;

  books.forEach(function(book) {
    Book.create(book, function(err, record) {
      if (err) return console.log(err);

      console.log('Record created:', record);

      count--;

      if (count === 0) {
        console.log('done');
        dataSource.disconnect();
      }
    });
  });
});