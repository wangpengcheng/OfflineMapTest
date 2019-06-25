<?php
	//文件的主要功能是接收记录id
	//返回连续的GPS坐标
	//
	//允许跨域访问
	header('Access-Control-Allow-Origin:*');
	//连接数据库；$conn为数据库聚丙函数
	include_once "re_connect.php";
	$json_raw = file_get_contents("php://input");
	$json_data = json_decode($json_raw);
	$result=array("result"=>"fail");

	//获得record_id;
	//$record_id=5;
	$record_id=$json_data->record_id;
	//echo json_encode($record_id);
	// $temp_id=$_POST["record_id"];
	// if($temp_id!=""){
	// 	$record_id=$temp_id;
	// }
	if($record_id!="")
	{
		//SELECT `gps_time`, `latitude`, `longitude` FROM `gps_record` WHERE record_id=5
		$gps_record_select_sql="SELECT gps_time, latitude, longitude FROM gps_record "." WHERE record_id = '".$record_id."'";
		//."limit 360 "

		$gps_result=$conn->query($gps_record_select_sql);
		$gps_row_count= mysqli_num_rows($gps_result);
		if($gps_row_count!==0){
			//将结果转化为数组
        	$result_array = $gps_result->fetch_all(MYSQLI_ASSOC);
        	$result["result"]=$result_array;
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
