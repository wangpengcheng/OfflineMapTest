<?php
/*
*php实现两点之间的等分插值
*输入：两点坐标：x1,y1
				x2,y2
		运行速度：car_speed;
		时间间隔：time_interval;
		思路：计算速度对应的dx，和dy;
		按照dx,dy输出
 输出：在两点内的时间间隔的经纬度坐标点
 设置公交类,直接输出公交参数和位置坐标
 
*/
header('Access-Control-Allow-Origin:*');

ini_set('memory_limit', '1024M');
	//设置时间；
	$t1 = microtime(true);
		//设置点类
	class GpsPoint{
			//x表示纬度，y表示经度
			public $x,$y;
			//设置构造函数
			//输入经度纬度
			public function __construct($iy,$ix){
				$this->x=$ix;
				$this->y=$iy;
			}
			public function get_x(){
				return $this->x;
			}
			public function get_y(){
				return $this->y;
			}
			public function set_x($new_x){
				$this->x=$new_x;
			}
			public function set_y($new_y){
				$this->y=$new_y;
			}
		}
		//设置线段类
		/*
	class GpsLine{
		public	$strat_point,$end_point;
		//斜率
		public  $line_lope;
		//存储除端点外的中间点
		public  $point_array;
		public  $sin_arg,$cos_arg;
		public function __construct(GpsPoint $istrat_point,GpsPoint $iend_point){
			$this->strat_point=$istrat_point;
			$this->end_point=$iend_point;
			//计算斜率
			$this->line_lope=($istrat_point->y-$iend_point->y)/($istrat_point->x-$iend_point->x);
			$temp_length=sqrt(pow(($istrat_point->y-$iend_point->y),2)+pow(($istrat_point->x-$iend_point->x),2));
			$this->cos_arg=($iend_point->x-$istrat_point->x)/$temp_length;
		    $this->sin_arg=($iend_point->y-$istrat_point->y)/$temp_length;
			$this->point_array=array();
			
		}
		public function point_array_add(GpsPoint $igps_point){
			array_push($this->point_array,$igps_point);
		}
		//输入点的实际间隔距离m；添加坐标点到point_array
		public function set_point_array($distance){
			
			$temp_x=$this->strat_point->x;
			$temp_y=$this->strat_point->y;
			//计算GPS对应步长
			$step_distance=$distance/100000;
			//计算对应x步长;
			$sin_arg=
			$dx=$step_distance*$this->cos_arg;
			$dy=$step_distance*$this->sin_arg;
			//$temp_x=0,$temp=0;
			//计算其x,y坐标范围
			if($this->strat_point->x<$this->end_point->x){
				$temp_xmin=$this->strat_point->x;
				$temp_xmax=$this->end_point->x;
			}else{
				$temp_xmin=$this->end_point->x;
				$temp_xmax=$this->strat_point->x;
			};
			if($this->strat_point->y<$this->end_point->y){
				$temp_ymin=$this->strat_point->y;
				$temp_ymax=$this->end_point->y;
			}else{
				$temp_ymin=$this->end_point->y;
				$temp_ymax=$this->strat_point->y;
			}
			//添加数据坐标点
			while($temp_xmin<=$temp_x&&$temp_x<=$temp_xmax&&$temp_ymin<=$temp_y&&$temp_y<=$temp_ymax){
				$temp_point=new GpsPoint($temp_x,$temp_y);
				$this->point_array_add($temp_point);
				$temp_x+=$dx;
				$temp_y+=$dy;
			};
			
		}
		
	}*/
	//设置公交类
	class Bus{
		//公交名称
		public $bus_name;
		//公交编号
		public $bus_num;
		//所在线路编号
		public $bus_line_num;
		//位置坐标
		public $bus_position;
		//运行速度
		public $bus_speed;
		//设置构造函数,利用数组进行构造；
		public function __construct($temp_input){
			//判断数组是否为空
			if(empty($temp_input)){
				$this->bus_name="ceshi";
				$this->bus_num=123456;
				$this->bus_line_num=1;
				$this->bus_position=new GpsPoint(30.6728020000,104.1386310000);
				$this->bus_speed=10;
			}else {
				$this->bus_name=$temp_input["bus_name"];
				$this->bus_num=$temp_input["bus_num"];
				$this->bus_line_num=$temp_input["line_num"];
				$this->bus_position=$temp_input["bus_position"];
				$this->bus_speed=$temp_input["bus_speed"];
			}
			
		}
		//设置公交名称
		public function SetBusNmae($var1){
			$this->bus_name=$var1;
		}
		//设置公交编号
		public function SetBusNumber($var1){
			$this->bus_num=$var1;
		}
		//设置所在线路编号
		public function SetBusLineNumber($var1){
			$this->bus_line_num=$var1;
		}
		//设置位置坐标
		public function SetBusPosition(GpsPoint $var1){
			$this->bus_position=$var1;
		}
		//设置运行速度
		public function SetBusSpeed($var1){
			$this->bus_speed=$var1;
		}
		//获取公交名称
		public function GetBusNmae(){
			return $this->bus_name;
		}
		//设置公交编号
		public function GetBusNumber(){
			return $this->bus_num;
		}
		//设置所在线路编号
		public function GetBusLineNumber(){
			return $this->bus_line_num;
		}
		//设置位置坐标
		public function GetBusPosition(){
			return $this->bus_position;
		}
		//设置运行速度
		public function GetBusSpeed(){
			return $this->bus_speed;
		}
		
	}
	//设置公交线路类
	class BusLine{
		//设置起点和终点站
		public $start_station,$end_station;
		//设置线段站点坐标
		public $station_arrary;
		//设置模拟线段端点
		public $bus_line_array;
		//线路产生模拟点
		public $line_point_array;
		//各点之间的实际间隔距离
		public $point_distance;
		//设置构造函数,输入GPS站点数组和终点起点站开始构造
		public function __construct(Array $ibus_line_array,Array $istation_array,GpsPoint $istart_station,GpsPoint $iend_station,$ipoint_distance){
			$this->bus_line_array=$ibus_line_array;
			$this->station_arrary=$istation_array;
			$this->start_station=$istart_station;
			$this->end_station=$iend_station;
			$this->point_distance=$ipoint_distance;
			$this->line_point_array=array();
		}
		//设置添加点函数
		public function line_array_add(GpsPoint $igps_point){
			array_push($this->line_point_array,$igps_point);
		}
		//设置添加线段函数,输入线段终点和起点差值添加
		public function set_point_array(GpsPoint $strat_point,GpsPoint $end_point,$ipoint_distance){
			
			$temp_array=array();
			$temp_x=$strat_point->x;
			$temp_y=$strat_point->y;
			//计算斜率
			$line_lope=($strat_point->y-$end_point->y)/($strat_point->x-$end_point->x);
			//计算cos,sin值；
			$temp_length=sqrt(pow(($strat_point->y-$end_point->y),2)+pow(($strat_point->x-$end_point->x),2));
			$cos_arg=($end_point->x-$strat_point->x)/$temp_length;
		    $sin_arg=($end_point->y-$strat_point->y)/$temp_length;
			//计算GPS对应步长
			$step_distance=$ipoint_distance/100000;
			//计算对应x步长;
			$dx=$step_distance*$cos_arg;
			$dy=$step_distance*$sin_arg;
			//$temp_x=0,$temp=0;
			//计算其x,y坐标范围
			if($strat_point->x<$end_point->x){
				$temp_xmin=$strat_point->x;
				$temp_xmax=$end_point->x;
			}else{
				$temp_xmin=$end_point->x;
				$temp_xmax=$strat_point->x;
			};
			if($strat_point->y<$end_point->y){
				$temp_ymin=$strat_point->y;
				$temp_ymax=$end_point->y;
			}else{
				$temp_ymin=$end_point->y;
				$temp_ymax=$strat_point->y;
			}
			//添加数据坐标点
			while($temp_xmin<=$temp_x&&$temp_x<=$temp_xmax&&$temp_ymin<=$temp_y&&$temp_y<=$temp_ymax){
				$temp_point=new GpsPoint($temp_x,$temp_y);
				//添加到临时数组
				//array_push($temp_array,$temp_point);
				$this->line_array_add($temp_point);
				$temp_x+=$dx;
				$temp_y+=$dy;
			};
		}
			//通过已有线段端点数组，循环添加插值坐标
		public function init_point_array(){
			//遍历$bus_line_array前后两个为一个线段进行插值
			$temp_array=$this->bus_line_array;
			//获取数组长度
			$array_length=count($temp_array);
			for($temp_i=0;$temp_i+1<$array_length;){
				
				//线段插值
				//echo gettype($temp_array[$temp_i+1]);
				$this->set_point_array($temp_array[$temp_i],$temp_array[$temp_i+1],$this->point_distance);
				$temp_i++;
			}
			//echo $array_length;
			//echo "</br>";
		}
			
	}
	
	
		$point1=new GpsPoint(30.5539600000,103.9963020000);
		$point2=new GpsPoint(30.5542520000,103.9961250000);
		$point3=new GpsPoint(30.5546600000,103.9958870000);
		$point4=new GpsPoint(30.5557010000,103.9950470000);
		$point5=new GpsPoint(30.5560220000,103.9948030000);
		$point6=new GpsPoint(30.5564330000,103.9946800000);
		$point7=new GpsPoint(30.5569180000,103.9946900000);
		$point8=new GpsPoint(30.5572690000,103.9947330000);
		$point9=new GpsPoint(30.5584380000,103.9951780000);
		$point10=new GpsPoint(30.5588650000,103.9954390000);
		$point11=new GpsPoint(30.5590940000,103.9956780000);
		$point12=new GpsPoint(30.5592320000,103.9958880000);
		$point13=new GpsPoint(30.5593950000,103.9961070000);
		$point14=new GpsPoint(30.5595890000,103.9965680000);
		$point15=new GpsPoint(30.5596990000,103.9969170000);
		$point16=new GpsPoint(30.5597620000,103.9974880000);
		$point17=new GpsPoint(30.5597770000,103.9982670000);
		$point18=new GpsPoint(30.5598080000,103.9985610000);
		$point19=new GpsPoint(30.5598950000,103.9990920000);
		$point20=new GpsPoint(30.5602040000,104.0001650000);
		$point21=new GpsPoint(30.5603960000,104.0011270000);
		$point22=new GpsPoint(30.5603170000,104.0014390000);
		$point23=new GpsPoint(30.5602060000,104.0017120000);
		$point24=new GpsPoint(30.5599520000,104.0020720000);
		$point25=new GpsPoint(30.5597300000,104.0023020000);			
		$point26=new GpsPoint(30.5589270000,104.0028600000);
		$point27=new GpsPoint(30.5587850000,104.0030220000);
		$point28=new GpsPoint(30.5585790000,104.0033470000);
		$point29=new GpsPoint(30.5579890000,104.0046160000);
		$point30=new GpsPoint(30.5576800000,104.0050660000);
		$point31=new GpsPoint(30.5569810000,104.0056800000);
		$point32=new GpsPoint(30.5554750000,104.0069890000);
		//添加数组
		$ipoint_array=array($point1,$point2,$point3,$point4,$point5,$point6,$point7,$point8,$point9,$point10,$point11,$point12,$point13,$point14,$point15,$point16,$point17,$point18,$point19,$point20,$point21,$point22,$point23,$point24,$point25,$point26,$point27,$point28,$point29,$point30,$point31,$point32);
		//设置实际距离;
		$idistance=10;
		//初始化公交线路
		$busline3=new BusLine($ipoint_array,$ipoint_array,$point1,$point32,$idistance);
		//生成线路坐标点
		$busline3->init_point_array();
		//设置获取位置
		$temp=0;
		$total=count($busline3->line_point_array);
		//设置bus初始化参数
		$temp_input=array();
		//初始化bus对象
		$layout_bus=new Bus($temp_input);
		//设置时间间隔
		//$interval=1;
		//设置显示实时输出
		//ignore_user_abort(true);//当用户关闭页面时服务停止
		//set_time_limit(0);  //设置执行时间，单位是秒。0表示不限制。
		//date_default_timezone_set('Asia/Shanghai');//设置时区
		//while(true){
			$now_time=time();
			if($temp>=$total){
				$temp=0;
			}else{
				$temp=$now_time%$total;
			}
			//获取坐标
			$temp_position=$busline3->line_point_array[$temp];
			//销毁数组
			unset($busline3->line_point_array);
			$layout_bus->SetBusPosition($temp_position);
			echo json_encode($layout_bus);
			
			//echo "</br>";
			//$t2 = microtime(true);
			//echo $t2-$t1.'<br />'.memory_get_usage()/1024;
			//设置睡眠时间
			//sleep($interval);
			//i++;
		//}
	//输出时间性能
	//echo "</br>";
	//$t2 = microtime(true);
	//echo $t2-$t1.'<br />'.memory_get_usage()/(1024*1024);
	
?>