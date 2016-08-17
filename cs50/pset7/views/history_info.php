<h3>History</h3>
<br>
<br>

<table class = "table table-striped">
	<tr>
		<th class="text-center">Transaction</th>
		<th class="text-center">Date and Time</th>
		<th class="text-center">Stock</th>
		<th class="text-center">Shares</th>
		<th class="text-center">Price</th>
	</tr>
 
	<?php foreach ($transactions as $transaction): ?>
		<tr>
			<td><?= $transaction["transaction"] ?></td>
			<td><?= $transaction["timestamp"] ?></td> 
			<td><?= $transaction["symbol"] ?></td> 
			<td><?= $transaction["shares"] ?></td> 
			<td><?= number_format( $transaction["price"],2,'.',','); ?></td>
		</tr>
		
	<?php endforeach ?>
 
</table>
