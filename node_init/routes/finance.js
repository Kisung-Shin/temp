var express = require('express');
var router = express.Router();
var mysql = require('mysql');
var conf = require('../conf/db');
var pool = mysql.createPool(conf.local);

router.get('/', function(req, res, next) {
  res.render('index', { title: 'Express' });
});

/* router select query in bigdata DB */
router.get('/open/:from_date/:to_date', function(req, res){

    var from_date = req.params.from_date,
    to_date = req.params.to_date;

    console.log(from_date, to_date);

    pool.getConnection(function(err, conn){
        conn.query('select Date,Open,High,Low,Close from finance_fb where Date between ? and ?',
        [from_date, to_date] ,function (err, rows){

            if(err) return res.status(500).json({error: err});
            if(!rows) return res.status(400).json({error: 'not found'});

            var msg = {
                status  : 'success',
                err     : '',
                result  : rows,
                length  : rows.length
            };
            res.json(msg);
        });
        conn.release();
    });
});

/* router insert query in bigdata DB */
//router.post('/:table/:begin/:end', function(req, res){});

/* router delete query in bigdata DB */
//router.delete('/:table/:begin/:end', function(req, res){});

module.exports = router;

