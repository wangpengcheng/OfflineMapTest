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
	//echo json_encode($result);
	//获得record_id;
	
	$record_id=$json_data->record_id;
	//$car_id=1;
	//$date_time="2019-06-20";
	//$date_time="";
	if($record_id!="")
	{
		//SELECT `video_path`, `video_path` FROM `re_video` WHERE record_id='5'
		$video_record_select_sql="SELECT video_name, video_path FROM re_video "." WHERE record_id = '".$record_id."'";
		//."limit 360 "

		$video_result=$conn->query($video_record_select_sql);
		$video_row_count= mysqli_num_rows($video_result);
		if($video_row_count!==0){
			//将结果转化为数组
        	$result_array = $video_result->fetch_all(MYSQLI_ASSOC);
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