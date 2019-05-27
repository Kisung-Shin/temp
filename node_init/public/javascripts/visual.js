$(document).ready(function(){

  $(function() {
      $("#datepicker1, #datepicker2").datepicker({
          dateFormat: 'yy-mm-dd'
      });
  }); 

  Date.prototype.getWeek = function() {
    var onejan = new Date(this.getFullYear(), 0, 1);
    var weeknum = Math.ceil((((this - onejan) / 86400000) + onejan.getDay() + 1) / 7)
    if (weeknum < 10)
      weeknum = "0" + weeknum;
    return weeknum;
  }

});

function convertDate(date) {
  var yyyy = date.getFullYear().toString();
  var mm = (date.getMonth()+1).toString();
  var dd  = date.getDate().toString();

  var mmChars = mm.split('');
  var ddChars = dd.split('');

  return yyyy + '-' + (mmChars[1]?mm:"0"+mmChars[0]) + '-' + (ddChars[1]?dd:"0"+ddChars[0]);
}

// plotly rendering
function drawingGraph(data, opt){
  Plotly.newPlot('myDiv', {
    data: data,
    layout: opt,
  });
}

// load facebook data by AJAX
function loadDailyTable(){

  var url = '';
  var from_date = document.getElementById("datepicker1").value;
  var to_date = document.getElementById("datepicker2").value;


  // setting date for query
  if(to_date.length == 0 || from_date == 0){
    from_date = "2017-02-02";
    to_date =  "2018-02-02";
  }

  url = "/finance/open/" + from_date + "/" + to_date;

  $.ajax({
    type: "GET",
    url: url,
    success:function(rows){
      parseDailyData(rows);      
      return false;
    },
    error:function(xhr, status, err){
      console.log(xhr.responseText);
      var err = '';
      $.each(JSON.parse(xhr.responseText), function(i, item){
        err += '<li>' + item.msg + '</li>';
      });
      console.log(err);
      return false;
    }

  });
}


// data parsing and set configuration
function parseDailyData(rows){

  _date_list  = [];
  _open_list = [];
  _high_list = [];
  _low_list = [];
  _close_list = [];


  data = rows.result;

  for(var idx = 0 ; idx < data.length; idx++){
    _date_list.push(data[idx].Date);
    _open_list.push(data[idx].Open);
    _high_list.push(data[idx].High);
    _low_list.push(data[idx].Low);
    _close_list.push(data[idx].Close);
  }

  var graph = {
    x : _date_list,
    y : _open_list,_high_list,_low_list,_close_list,
    name : "open/high/low/close count",
    mode: 'lines+markers',
    marker: {
    size: 10,
    line: { width: 0.5 },
    opacity: 0.8
    }
  }

  title_type = 'FACEBOOK RECENT OPEN PRICE';

  var opt = {
    title: title_type,
    titlefont: {
      family: 'Courier New, monospace',
      size: 24,
      color: '#7f7f7f'
    },
    xaxis: {
      title: 'DAILY',
      titlefont: {
        family: 'Arial, sans-serif',
        size: 15,
        color: 'lightgrey'
      },
      showticklabels: true,
      tickfont: {
        family: 'Old Standard TT, serif',
        size: 13,
        color: 'black'
      },
      showgrid: true,
      zeroline: true,
      showline: true,
      mirror: 'ticks',
      gridcolor: '#bdbdbd',
      gridwidth: 2,
      zerolinecolor: '#969696',
      zerolinewidth: 4,
      linecolor: '#636363',
      linewidth: 6
    },
    margin: {
      l: 50,
      r: 50,
      b: 150,
      t: 150,
      pad: 4
    },
  };

  drawingGraph([graph], opt);

}



