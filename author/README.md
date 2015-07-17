
Steps to install and Run the app:

For Database on MangoDB:
1. Run MongoDB Service on localhost
2. <On MongoDB: use freshDB>

cd to the main directory and run following commands:
1. npm install
2. git config --global url."https://".insteadOf git://
3. bower install angular angular-resource angular-ui-router bootstrap
4. node server/bin/automigrate.js
5. node .


Assumptions:
This application adds a functionality to authenticate the user by using:
username: user
password: secret
<This has been hard coded for now>
<Also I am not maintaining any cookies or session for now>

MongoDB Service should be on on local host:
Database name: freshDB

