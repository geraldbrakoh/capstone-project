<?php

        //local
        $servername="localhost";
        $username="id18780255_geraldb";
        $password="Rey Mysterio619";
        $dbname="id18780255_capstone_bms";
        
        $con = mysqli_connect($servername,$username,$password,$dbname) or die ("could not connect data");

//echo "Welcome to the database of the Battery Management System!";
    //include("./config.php");
    $data=[];

    if(isset($_GET['table'])){
      if($_GET['table']==1){
        $query=mysqli_query($con,"select * from `battery_details` where id between 201 and 212");
        $data=mysqli_fetch_all($query,MYSQLI_ASSOC);
    }
    // if($_GET['listing']==2){
    //     $query=mysqli_query($con,"select `average_reading` from `monitoring_system` ");
    //     $data=mysqli_fetch_all($query,MYSQLI_ASSOC);
    // }
  } 
?>

<!DOCTYPE html>
<html lang="en">
  <head>
    <!-- Required meta tags -->
    <meta charset="utf-8" />
    <meta
      name="viewport"
      content="width=device-width, initial-scale=1, shrink-to-fit=no"
    />
    <link
      href="https://fonts.googleapis.com/css?family=Roboto:300,400&display=swap"
      rel="stylesheet"
    />

    <link rel="stylesheet" href="fonts/icomoon/style.css" />

    <link rel="stylesheet" href="owl.carousel.min.css" />

    <!-- Bootstrap CSS -->
    <link rel="stylesheet" href="bootstrap.min.css" />

    <!-- Style -->
    <link rel="stylesheet" href="table.css" />

    <title>Battery Management System Database Table</title>
  </head>
  <body>
    <div class="content">
      <div class="container">
        <h2 class="mb-5">Battery Management System Database Table</h2>

        <div class="table-responsive">
          <table class="table table-striped custom-table">
            <thead>
              <tr>
                <th scope="col">ID</th>
                <th scope="col">V1</th>
                <th scope="col">V2</th>
                <th scope="col">V3</th>
                <th scope="col">V4</th>
                <th scope="col">TEMP 1</th>
                <th scope="col">TEMP 2</th>
                <th scope="col">CURRENT</th>
                <th scope="col"></th>
              </tr>
            </thead>

            <?php foreach($data as $dataItem) { ?>

            <tbody>
              <tr scope="row">
                <td> <?php echo $dataItem["id"] ?> </td>
                <td><?php echo $dataItem["voltage1"] ?></td>
                <td>
                  
                  <small class="d-block"
                    ><?php echo $dataItem["voltage2"] ?></small
                  >
                </td>
                <td><?php echo $dataItem["voltage3"] ?></td>
                <td><?php echo $dataItem["voltage4"] ?></td>
                <td><?php echo $dataItem["temp1"] ?></a></td>
                <td><?php echo $dataItem["temp2"] ?></a></td>
                <td><?php echo $dataItem["current"] ?></a></td>
              </tr>
            <?php } ?>
              
            </tbody>

            
          </table>
        </div>
      </div>
    </div>

    <script src="js/jquery-3.3.1.min.js"></script>
    <script src="js/popper.min.js"></script>
    <script src="js/bootstrap.min.js"></script>
    <script src="js/main.js"></script>
  </body>
</html>
