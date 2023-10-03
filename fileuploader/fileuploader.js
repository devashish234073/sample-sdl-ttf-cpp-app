const http = require('http');
const fs = require('fs');
const path = require('path');

const port = 3000;
const uploadDir = path.join(__dirname, 'uploads');

// Create the HTTP server
const server = http.createServer((req, res) => {
  if (req.method === 'GET') {
    const fileName = req.url.replace(/^\/read\//, '');
    const filePath = path.join(uploadDir, fileName);

    if (fs.existsSync(filePath)) {
      const fileStream = fs.createReadStream(filePath);

      res.setHeader('Content-Disposition', `attachment; filename=${fileName}`);
      res.setHeader('Content-Type', 'application/octet-stream');

      fileStream.pipe(res);
    } else {
      res.writeHead(404, { 'Content-Type': 'text/plain' });
      res.end('File not found.');
    }
  } else if (req.url === '/upload' && req.method === 'POST') {
    const fileName = path.basename(req.headers['content-disposition'].split(';')[1].trim().split('=')[1], '"');

    const filePath = path.join(uploadDir, fileName);
    console.log("starting to upload "+filePath);
    const writeStream = fs.createWriteStream(filePath);

    req.on('data', (chunk) => {
      writeStream.write(chunk);
    });

    req.on('end', () => {
      writeStream.end();
      res.writeHead(200, { 'Content-Type': 'text/plain' });
      console.log("file uploaded..");
      res.end('File uploaded successfully.');
    });

    req.on('error', (err) => {
      console.error(err);
      res.writeHead(500, { 'Content-Type': 'text/plain' });
      res.end('Internal Server Error');
    });
  } else {
    res.writeHead(404, { 'Content-Type': 'text/plain' });
    res.end('Not Found');
  }
});

// Start the server
server.listen(port, () => {
  console.log(`Server is running on port ${port}`);
});
