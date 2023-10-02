# sample-sdl-ttf-cpp-app

The sources and cloudbuild.yaml in this repo is created using chatGPT here's the link to the complete conversation of the same --> https://chat.openai.com/share/ada421ef-3766-41ec-9b20-d56000bfa956

I have uploaded a fileuploader nodejs file which can be run in a compute instance and it exposes an upload api

## In local env for example I can run the following curl command to upload a file teh instance running the fileuploader.js
 curl -X POST -H "Content-Disposition: attachment; filename=test.txt" -F "file=@./test.txt" http://localhost:3000/upload

 Note : please replace localhost with the public IP of the compute instance and make sure traffic allowed on PORT 3000.

 We can use this api to modify the cloudbuild.yaml file so that after a successful build it call this api with file names replaced with the artifact name that gets created in the build process 

 And we will have our upload step also working
