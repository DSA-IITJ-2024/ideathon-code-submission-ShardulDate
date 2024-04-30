document.getElementById('preferences-form').addEventListener('submit', function(event) {
    // Prevent the form from being submitted to the server
    event.preventDefault();

    // Get the selected options
    var userid = document.getElementById('userid').value;
    var subject = document.getElementById('subject').value;
    var classroom = document.getElementById('classroom').value;
    var timeslot = document.getElementById('timeslot').value;

    // Check if any preference is set to "Please select", if so, set it to NULL
    userid = (userid === "Please select") ? "NULL" : userid;
    subject = (subject === "Please select") ? "NULL" : subject;
    classroom = (classroom === "Please select") ? "NULL" : classroom;
    timeslot = (timeslot === "Please select") ? "NULL" : timeslot;

    // Create an object with the data
    var data = {
        userid: userid,
        subject: subject,
        classroom: classroom,
        timeslot: timeslot
    };

    // Send the data to the server
    fetch('http://localhost:3000/', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json'
        },
        body: JSON.stringify(data)
    }).then(function(response) {
        return response.json();
    }).then(function(data) {
        console.log('Data sent successfully:', data);
    }).catch(function(error) {
        console.error('Error:', error);
    });
});