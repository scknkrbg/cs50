<div>
    <style type="text/css">
        table, td, th {
            margin-left: auto;
            margin-right: auto;
            width: 150px;
            table-layout: fixed;
            text-align: center;
            border: 1px solid black;
        }
        
    </style>

    <table>
        <tr>
            <th>Symbol</th>
            <th>Shares Owned</th>
            <th>Bought Price</th>
            <th>Current Value</th>
            <th>Profit / Loss</th>
        </tr>
        <tr style="font-weight: bold;" >
            <td><?= "CASH" ?></td>
            <td><?= "" ?></td>
            <td><?= "" ?></td>
            <td><?= "$". number_format($cash, 2, ',', '.') ?></td>
            <td><?= "" ?></td>
        </tr>
        
        <?php 
            
            $total_profit = 0;
            foreach($portfolios as $portfolio)
            {
                $market_price = lookup($portfolio["symbol"]);
                $net_profit = $portfolio["active_quantity"] * ($market_price["price"] - $portfolio["bought_price"]);
                $total_profit += $net_profit; 
            
                print("<tr>");
                print("<td>" . $portfolio["symbol"] . "</td>");
                print("<td>" . number_format($portfolio["active_quantity"], 0, ',', '.') . "</td>");
                print("<td>" . "$" . number_format($portfolio["bought_price"], 2, ',', '.') . "</td>");
                print("<td>" . "$" . number_format($market_price["price"], 2, ',', '.') . "</td>");
                print("<td>" . "$" . number_format($net_profit, 2, ',', '.') . "</td>");
                print("</tr>");
            };
                
               
            
        
        ?>
         <tr style="font-weight: bold;" >
            <td><?= "TOTAL" ?></td>
            <td><?= "" ?></td>
            <td><?= "" ?></td>
            <td><?= "" ?></td>
            <td><?= "$". number_format($total_profit, 2, ',', '.') ?></td>
        </tr>
    </table>
</div>