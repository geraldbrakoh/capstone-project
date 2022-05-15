<?php
    
$servername="localhost";
$username="id18780255_geraldb";
$password="Rey Mysterio619";
$dbname="id18780255_capstone_bms";

$con = mysqli_connect($servername,$username,$password,$dbname) or die ("could not connect data");




    if(isset($_GET['insert']))
    {
        $voltage1=$_GET['voltage1'];
        $voltage2=$_GET['voltage2'];
        $voltage3=$_GET['voltage3'];
        $voltage4=$_GET['voltage4'];
        $temp1=$_GET['temp1'];
        $temp2=$_GET['temp2'];
        $current=$_GET['current'];


        $sql="INSERT INTO `battery_details` (`voltage1`, `voltage2`, `voltage3`,`voltage4`, `temp1`, `temp2`, `current`) VALUES (";
        $sql2="'$voltage1', '$voltage2', '$voltage3','$voltage4','$temp1','$temp2','$current')";
        $sql=$sql.$sql2;
        $query =mysqli_query($con,$sql);
    
    if ($query)
        echo "success";
    else 
        echo "error".mysqli_error($con);
    }

?>