<?php
	//文件的主要功能是接收
	//记录时间、 开始时间、视频名字和位置，返回记录的主要索引值 record_id;
	//输入开始时间，车辆编号，返回记录的id
	//允许跨域访问
	header('Access-Control-Allow-Origin:*');
	//连接数据库；$conn为数据库聚丙函数
	include_once "re_connect.php";
	$result=array("result"=>"fail");
	//通过json来接收数据
	$json_raw = file_get_contents("php://input");
	$json_data = json_decode($json_raw);
	//获取记录时间
	$record_time=$json_data->record_time;
	//获取车辆id
	$car_id=$json_data->car_id;

	if($record_time!=""&&
		$car_id!="")
	{
		$record_sql="INSERT INTO re_record (record_time,car_id) VALUES ('".$record_time."','".$car_id."');";

		if($conn->query($record_sql)){
			//$result=array("result"=>mysqli_insert_id($conn));
			$result["result"]=mysqli_insert_id($conn);//输出record_id
		}else{
			$result["result"]="insert fail";			
		}
	}else{
		$result["result"]="input error";
	}
	echo json_encode($result);
?>
