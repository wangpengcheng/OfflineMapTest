<?php
	//文件的主要功能是接收
	//实现GPS的插入
	//sql example :INSERT INTO `gps_record` (`record_id`, `gps_time`, `latitude`, `longitude`) VALUES ('5', CURRENT_TIMESTAMP, '30.6311', '104.082');
	//input :time latitude, longitude
	//允许跨域访问
	header('Access-Control-Allow-Origin:*');
	//连接数据库；$conn为数据库聚丙函数
	include_once "re_connect.php";
	$json_raw = file_get_contents("php://input");
	$json_data = json_decode($json_raw);
	$result=array("result"=>"fail");
	//GPS位置所属的记录位置
	//$record_id=5;
	//$record_id=$_POST["record_id"];
	$record_id=$json_data->record_id;
	//开始时间
	//$gps_time="2019-12-05 00:00:00.0000";
	//$gps_time="CURRENT_TIMESTAMP";
	//$gps_time=$_POST["gps_time"];
	$gps_time=$json_data->gps_time;
	//纬度
	//$latitude="30.5563134";
	//$latitude=$_POST["latitude"];
	$latitude=$json_data->latitude;
	//经度
	//$longitude="103.99384";
	//$longitude=$_POST["longitude"];
	$longitude=$json_data->longitude;

	if($gps_time!=""&&
	   $latitude!=""&&
	   $longitude!=""&&
		$record_id!="")
	{
		$gps_record_sql="INSERT INTO gps_record (record_id,latitude,longitude,gps_time) VALUES ('".$record_id."','".$latitude."','".$longitude."','".$gps_time."')";

		if($conn->query($gps_record_sql)){
			$result["result"]="insert sccuss";			
		}else{
			$result["result"]="insert failed";
		}
	}else{
		$result["result"]="input error";
	}
	echo json_encode($result);
	// $json_raw = file_get_contents("php://input");
	// $json_data = json_decode($json_raw);
	// echo json_encode($json_raw);
?>
