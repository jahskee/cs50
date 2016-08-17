<!DOCTYPE html>

<html>

    <head>

        <!-- http://getbootstrap.com/ -->
    <link href="/css/bootstrap.min.css" rel="stylesheet"/> 

        <link href="/css/styles.css" rel="stylesheet"/>

        <?php if (isset($title)): ?>
            <title>C$50 Finance: <?= htmlspecialchars($title) ?></title>
        <?php else: ?>
            <title>C$50 Finance</title>
        <?php endif ?>

        <!-- https://jquery.com/ -->
        <script src="/js/jquery-1.11.3.min.js"></script>

        <!-- http://getbootstrap.com/ -->
        <script src="/js/bootstrap.min.js"></script>

        <script src="/js/scripts.js"></script>
        
        <?php
            
        ?>

    </head>

    <body>
      
        <div class="container">
    
            <div id="top">
          
                 
                <div>
                    <table align="center">
                        <tr>
                            <?php
                            if(!empty($_SESSION["username"])){
                            ?>
                                <td style="width:100px"></td>
                           <?php
                               }
                            ?>                             
                                <td>
                                        <a href="/"><img alt="C$50 Finance" src="/img/logo.png"/></a>            
                                </td>
                                
                            <?php
                            
                            if(!empty($_SESSION["username"])){
                            ?>
                                <td style="width:100px">
                                    
                                </td>
                                
                                <td>
                                 User:&nbsp; <?= $_SESSION["username"] ?><br> <a href="/logout.php">Log out</a>
                                </td>
                              <?php 
                                }
                            ?>
                        </tr>
                        
                    </table>
                    
                    
                </div>
                <?php if (!empty($_SESSION["user_id"])): ?>
          <div><br>
          <br>
          
 <a href="/" class="myButton">Portfolio</a>&nbsp;&nbsp;              
 <a href="quote.php" class="myButton">Quote</a>&nbsp;&nbsp;
 <a href="buy.php" class="myButton">Buy</a>&nbsp;&nbsp;
 <a href="sell.php" class="myButton">Sell</a>&nbsp;&nbsp;
 <a href="history.php" class="myButton">History</a>&nbsp;&nbsp;
 <a href="deposit.php" class="myButton">Deposit</a>
 
	<br>
</div>

                <?php endif ?>
            </div>
        
            <div id="middle">
                
   