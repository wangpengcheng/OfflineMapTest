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
	
	if(empty($json_data->car_id)){
		$car_id="";
	}else{
		$car_id=$json_data->car_id;
	};
	//$car_id=1;
	//$date_time="2019-06-20";
	//$date_time="";
	if($car_id=="")
	{
		//SELECT car_id FROM `re_record`GROUP BY car_id
		$car_select_sql="SELECT car_id FROM re_record GROUP BY car_id;";
	}else{
		//SELECT `car_id` FROM `re_record` WHERE DATE_FORMAT(record_time,'%Y-%m-%d')='2019-06-20' 
		$car_select_sql="SELECT DATE_FORMAT(record_time,'%Y-%m-%d') AS record_date FROM re_record WHERE car_id='".$car_id."' GROUP BY record_date";
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