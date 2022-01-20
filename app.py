from flask import Flask, render_template, request
# import requests
from models import predict

app = Flask(__name__)

@app.route('/', methods=["GET", "POST"])
def home():
    return render_template("index.html")

@app.route('/data', methods=['GET', 'POST'])
def data():
    return render_template("data.html")

@app.route('/getData', methods=['GET', 'POST'])
def getStats():
    data = predict.ml()
    plots = data[1]
    #print(data)
    return render_template("data.html", data=data[0], plots = plots)
    
        

if __name__ == '__main__':
     app.run(debug=True)
