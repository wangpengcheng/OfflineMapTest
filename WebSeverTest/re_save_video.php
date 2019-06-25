<?php
	//文件的主要功能是接收
	//记录时间、 开始时间、视频名字和位置，返回记录的主要索引值 record_id;
	//输入开始时间，车辆编号，返回记录的id
	//允许跨域访问
	header('Access-Control-Allow-Origin:*');
	//连接数据库；$conn为数据库聚丙函数
	include_once "re_connect.php";
	//开始时间
	//$record_time="2019-12-05 00:00:00.0000";
	//$record_time=$_POST["record_time"];
	//车辆编号
	//$car_id=$_POST["car_id"];
	//$car_id=1;
	// //视频名称
	// //$video_name="test1";
	// $video_name=$_POST["video_name"];
	// //视频文件位置
	// //$video_path="test2";
	// $video_path=$_POST["video_path"];
	//
	//通过json来接收数据
	$json_raw = file_get_contents("php://input");
	$json_data = json_decode($json_raw);
	//获取记录时间
	$start_time=$json_data->start_time;
	//获取车辆id
	$record_id=$json_data->record_id;
	//获取视频名称
	$video_name=$json_data->video_name;
	//获取视频路径
	$video_path=$json_data->video_path;

	if($start_time!=""&&
		$record_id!=""&&
		$video_name!=""&&
		$video_path!="")
	{
		$record_sql="INSERT INTO re_video (start_time,record_id,video_name,video_path) VALUES ('".$start_time."','".$record_id."','".$video_name."','".$video_path."');";

		if($conn->query($record_sql)){
			//$result=array("result"=>mysqli_insert_id($conn));
			echo json_encode(mysqli_insert_id($conn));//输出record_id
		}else{
			echo json_encode("insert fail");			
		}
	}else{
		echo json_encode("input error");
	}
?>
