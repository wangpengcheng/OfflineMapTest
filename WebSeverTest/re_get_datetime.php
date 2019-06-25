<?php
	//文件的主要功能是接收记录id
	//返回连续的GPS坐标
	//允许跨域访问
	header('Access-Control-Allow-Origin:*');
	//连接数据库；$conn为数据库聚丙函数
	include_once "re_connect.php";
	$json_raw = file_get_contents("php://input");
	$json_data = json_decode($json_raw);
	$result=array("result"=>"fail");
	
	//根据输出决定输出日期还是时间，
	//$record_id=5;
	$car_id=$json_data->car_id;
	$record_date=$json_data->record_date;
	if(empty($json_data->start_time)){
		$start_time="";
	}else{
		$start_time=$json_data->start_time;
	}
	// $start_time="17:43:48";
	// $record_date="2019-06-20";
	// $car_id=1;
	if($start_time=="")
	{
		$car_select_sql="SELECT DATE_FORMAT(record_time,'%H:%i:%s') AS start_time FROM re_record WHERE DATE_FORMAT(record_time,'%Y-%m-%d')='".$record_date."'AND car_id='".$car_id."'";
	}else{
		//SELECT `car_id` FROM `re_record` WHERE DATE_FORMAT(record_time,'%Y-%m-%d')='2019-06-20' 
		$car_select_sql="SELECT  record_id FROM re_record WHERE record_time='".$record_date." ".$start_time."'AND car_id='".$car_id."'";
	}
	$car_result=$conn->query($car_select_sql);
	$car_row_count= mysqli_num_rows($car_result);
	if($car_row_count!==0){
			//将结果转化为数组
        	$result_array = $car_result->fetch_all(MYSQLI_ASSOC);
        	$result["result"]=$result_array;
     }else{
		
			$result["result"]="select result is empty";
	}
	echo json_encode($result);
	// $json_raw = file_get_contents("php://input");
	// $json_data = json_decode($json_raw);
	// echo json_encode($json_raw);
?>  