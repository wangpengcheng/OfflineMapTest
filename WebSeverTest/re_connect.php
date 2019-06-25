<?php
//connect localhost
$sever_ip="localhost";//sever ip adress
$mysql_user_name="peng";//mysql user name
//$mysql_user_password="g59w1P0NSs";//mysql pass word
$mysql_user_password="peng";//mysql pass word
$mysql_database_name="review_data";//database name
//useing mysqli in php7
$conn=new mysqli($sever_ip,
		    	$mysql_user_name,
		    	$mysql_user_password,
		    	$mysql_database_name);
if($conn->connect_errno){
        die('Connect Error:'.$conn->connect_error);
    } else {
        //echo "connect ok!!!!" ;
    };
     //set deaful charset utf-8
    $conn->set_charset('utf8');

?>
