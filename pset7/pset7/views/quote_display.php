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
            <th>Name</th>
            <th>Price</th>
        </tr>
        <tr>
            <td><?= $symbol?></td>
            <td><?= $name ?></td>
            <td><?= "$".number_format($price, 2, ',', '.') ?></td>
        </tr>
    </table>
</div>

