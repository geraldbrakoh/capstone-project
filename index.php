<?php

//local
$servername="localhost";
$username="id18780255_geraldb";
$password="Rey Mysterio619";
$dbname="id18780255_capstone_bms";

$con = mysqli_connect($servername,$username,$password,$dbname) or die ("could not connect data");

//echo "Welcome to the database of the Battery Management System!";
?>

<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="utf-8" />
    <meta
      name="viewport"
      content="width=device-width, initial-scale=1, shrink-to-fit=no"
    />
    <meta name="description" content="" />
    <meta name="Gerald" content="" />
    <title>Battery Management System</title>
    <!-- Favicon-->
    <!-- Font Awesome icons (free version)-->
    <script
      src="https://use.fontawesome.com/releases/v6.1.0/js/all.js"
      crossorigin="anonymous"
    ></script>
    <!-- Google fonts-->
    <link
      href="https://fonts.googleapis.com/css?family=Montserrat:400,700"
      rel="stylesheet"
      type="text/css"
    />
    <link
      href="https://fonts.googleapis.com/css?family=Roboto+Slab:400,100,300,700"
      rel="stylesheet"
      type="text/css"
    />
    <!-- Core theme CSS (includes Bootstrap)-->
    <link href="styles.css" rel="stylesheet" />
  </head>
  <body id="page-top">
    <!-- Navigation-->
    <nav class="navbar navbar-expand-lg navbar-dark fixed-top" id="mainNav">
      <div class="container">
        <button
          class="navbar-toggler"
          type="button"
          data-bs-toggle="collapse"
          data-bs-target="#navbarResponsive"
          aria-controls="navbarResponsive"
          aria-expanded="false"
          aria-label="Toggle navigation"
        >
          Menu
          <i class="fas fa-bars ms-1"></i>
        </button>
        <div class="collapse navbar-collapse" id="navbarResponsive">
          <ul class="navbar-nav text-uppercase ms-auto py-4 py-lg-0">
            <li class="nav-item">
              <a class="nav-link" href="#services">SERVICES</a>
            </li>
            <li class="nav-item">
              <a class="nav-link" href="#about">ABOUT</a>
            </li>
          </ul>
        </div>
      </div>
    </nav>
    <!-- Masthead-->
    <header class="masthead">
      <div class="container">
        <div class="masthead-subheading">
          Welcome To Our Page, It's Nice To Meet You!
        </div>
        <div class="masthead-heading text-uppercase">
          Check your battery info
        </div>
        <a class="btn btn-primary btn-xl text-uppercase" href="table.php?table=1"
          >Check Database</a
        >
      </div>
    </header>
    <section class="page-section" id="services">
      <div class="container">
        <div class="text-center">
          <h2 class="section-heading text-uppercase">Services</h2>
          <h3 class="section-subheading text-muted">
            Check out our services tab!
          </h3>
        </div>
        <div class="row text-center">
          <div class="col-md-4">
            <span class="fa-stack fa-4x">
              <i class="fa-solid fa-car-battery"></i>
            </span>
            <h4 class="my-3">Battery Health</h4>
            <p class="text-muted">
              A good battery should have a voltage of 16.8 volts. If you see a
              reading of less than 10 volts, the battery is weak and needs
              recharging or replacement.
            </p>
          </div>
          <div class="col-md-4">
            <span class="fa-stack fa-4x">
              <i class="fa-solid fa-car-burst"></i>
            </span>
            <h4 class="my-3">Car Damage</h4>
            <p class="text-muted">
              It is a good practise to check your car daily for damages. Please
              contact our services when you notice any damages to your car
              battery.
            </p>
          </div>
          <div class="col-md-4">
            <span class="fa-stack fa-4x">
              <i class="fa-solid fa-triangle-exclamation fa-fade"></i>
            </span>
            <h4 class="my-3">Car Alert signals</h4>
            <p class="text-muted">
              If the battery warning light (a blinking LED and a buzzer) on the dashboard comes on while you’re driving means, The
              cause of the battery light could be the damageof various cells in the battery pack,overheating of the pack of overcurrent.
            </p>
          </div>
        </div>
      </div>
    </section>
    <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/js/bootstrap.bundle.min.js"></script>
    <script src="js/scripts.js"></script>

    <script src="https://cdn.startbootstrap.com/sb-forms-latest.js"></script>
  </body>
</html>
