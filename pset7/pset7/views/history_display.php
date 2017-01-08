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
            <th>Bought Date</th>
            <th>Sold Date</th>
            <th>Symbol</th>
            <th># of Shares Bought</th>
            <th>Bought Price</th>
            <th># of Shares Sold</th>
            <th>Sold Price</th>
            <th>Profit / Loss Per Share</th>
            <th> Total Profit / Loss</th>
        </tr>
        <!--<tr style="font-weight: bold;" >-->
        <!--    <td><?= "CASH" ?></td>-->
        <!--    <td><?= "" ?></td>-->
        <!--    <td><?= "" ?></td>-->
        <!--    <td><?= "$". number_format($cash, 2, ',', '.') ?></td>-->
        <!--    <td><?= "" ?></td>-->
        <!--</tr>-->
        
        <?php 
            
            $total_profit = 0;
            foreach($history as $portfolio)
            {
                $total_profit += $portfolio["profit_total"]; 
                print("<tr>");
                print("<td>" . $portfolio["date_bought"] . "</td>");
                print("<td>" . $portfolio["date_sold"] . "</td>");
                print("<td>" . $portfolio["symbol"] . "</td>");
                print("<td>" . number_format($portfolio["bought_quantity"], 0, ',', '.') . "</td>");
                print("<td>" . "$" . number_format($portfolio["bought_price"], 2, ',', '.') . "</td>");
                print("<td>" . number_format($portfolio["sold_quantity"], 0, ',', '.') . "</td>");
                print("<td>" . "$" . number_format($portfolio["sold_price"], 2, ',', '.') . "</td>");
                print("<td>" . "$" . number_format($portfolio["profit_per_share"], 2, ',', '.') . "</td>");
                print("<td>" . "$" . number_format($portfolio["profit_total"], 2, ',', '.') . "</td>");
                print("</tr>");
            };
                
               
            
        
        ?>
         <tr style="font-weight: bold;" >
            <td><?= "TOTAL" ?></td>
            <td><?= "" ?></td>
            <td><?= "" ?></td>
            <td><?= "" ?></td>
            <td><?= "" ?></td>
            <td><?= "" ?></td>
            <td><?= "" ?></td>
            <td><?= "" ?></td>
            <td><?= "$". number_format($total_profit, 2, ',', '.') ?></td>
        </tr>
    </table>
</div>