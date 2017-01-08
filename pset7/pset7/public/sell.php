<?php
	
	// configuration
	require("../includes/config.php");

	// if user reached page via GET (a by clicking or via redirect)
	if($_SERVER["REQUEST_METHOD"] == "GET")
	{
		// else render form
		render("sell_form.php", ["title" => "Sell"]);
	} 
	
	else if ($_SERVER["REQUEST_METHOD"] == "POST")
	{
		if(empty($_POST["symbol"]))  //or empty($_POST["password"]) or ($_POST["password"] != $_POST["confirmation"]))
		{
			apologize("Empty symbol means sell everything?");
		}
		else if(empty($_POST["shares"]))
		{
			apologize("Empty share number means sell all of them?");
		}
		else
		{
		    // looking up current share price
			$symbol_current = lookup($_POST["symbol"]);
	
			$s_price = $symbol_current["price"];
 			// looking up the share in the portfolio table
			$total_check = CS50::query("SELECT sum(active_quantity) as active_quantity FROM portfolio 
			WHERE status=1 and user_id = ? and symbol = ? GROUP BY user_id", $_SESSION["id"], $_POST["symbol"]);
			
			$symbol_check = CS50::query("SELECT * FROM portfolio WHERE status=1 and user_id = ? and symbol = ? ", 
			$_SESSION["id"], $_POST["symbol"]);
			
			if($symbol_check[0]["symbol"] != $_POST["symbol"])
			{
				apologize("You do not have active investments on this shares!");
			}
			else
			{
				if($_POST["shares"] > $total_check[0]["active_quantity"] or $_POST["shares"] <= 0)
				{
				    apologize("Please check number of available shares to sell!");
				}
				else //if($_POST["shares"] == $total_check[0]["active_quantity"])
				{
				    // portfolio table updates
				    $i = $_POST["shares"];
				    foreach($symbol_check as $s)
				    {
				    	if($i >= $s["active_quantity"] and $i > 0 )
				    	{
				    		$i = $i - $s["active_quantity"];
				    		
				    		$q = $s["active_quantity"];
				    		
				    		$passivate_symbol = CS50::query("UPDATE portfolio SET active_quantity=0, status=0 WHERE id = ?", 
				    		$s["id"]);
				    		
				    		$make_history = CS50::query("INSERT INTO history (portfolio_id, user_id, sold_quantity, sold_price)
				    		VALUES (?, ?, ?, ?)", $s["id"], $_SESSION["id"], $q, $s_price);
				    		
				    		$update_cash = CS50::query("UPDATE users SET cash = cash + ? WHERE id = ?", $s_price * $q, $_SESSION["id"]);
				    	}
				    	else 
				    	{
				    		$passivate_symbol = CS50::query("UPDATE portfolio SET active_quantity = active_quantity - ?  WHERE id = ?", 
				    		$i, $s["id"]);
				    		
				    		$make_history = CS50::query("INSERT INTO history (portfolio_id, user_id, sold_quantity, sold_price)
				    		VALUES (?, ?, ?, ?)", $s["id"], $_SESSION["id"], $i, $s_price);
				    		
				    		$update_cash = CS50::query("UPDATE users SET cash = cash + ? WHERE id = ?", $s_price * $i, $_SESSION["id"]);
				    		
				    		$i = 0;
				    		
				    	}
				    }
				    
				 
				redirect("index.php");
				}
			}
		}
	}
?>