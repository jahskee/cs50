<?php
   // configuration
    require_once("../includes/config.php"); 

    $user_id = $_SESSION["user_id"];
    $portfolios= CS50::query("SELECT * FROM portfolio where user_id=?", $user_id);
			
    $users= CS50::query("SELECT cash FROM users where id=?", $user_id);
?>
		
<div class = "title" >
	<h3>Portfolio</h3>
</div>
<br><br>
<div style="text-align:left">
	<b>
Cash Balance: $<?= number_format($users[0]["cash"],2,'.',',');?>
</b>
<br>
</div>
<div>
	
	<table class = "table table-striped">
	   <thead>
        <tr>
            <th class="text-center">Symbol</th>
            <th class="text-center">Name</th>
            <th class="text-center">Shares</th>
            <th class="text-center">Price</th>
            <th class="text-center">TOTAL</th>
        </tr>
    </thead>
	
		
		
		<?php
		$ovl_total=0;
		foreach ($portfolios as $portfolio): ?>
		    <?php
		    	$stock = lookup($portfolio["symbol"]);
		    	$stock_total = $portfolio["shares"]*$stock["price"];
		    	$ovl_total=$ovl_total+$stock_total;
		    	
		    ?>
			<tr>
				<td><?= $stock["symbol"] ?></td> 
				<td><?= $stock["name"] ?></td> 
				<td><?= $portfolio["shares"] ?></td>
				<td><?= $stock["price"] ?></td> 
				<td><?= number_format($stock_total,2,'.',',') ?></td> 
			</tr>
			
		<?php endforeach ?>
	
		<tr>
			<td></td>
			<td></td>
			<td></td>
			<td> <b>Total</b></td>
			<td><b><?= number_format($ovl_total,2,'.',','); ?> </b> </td>
		</tr>
	
	</table>
</div>
