from django.shortcuts import render
from django.http import HttpResponse, JsonResponse
from django.template import loader
from urllib.parse import unquote
import subprocess
import ast

# Create your views here.
def index(request):
    context = {}
    return render(request, "portfolio/index.html", context)

def tsp(request):
    context = {}
    return render(request, "portfolio/tsp.html", context)

"""
call "main" which is the traveling salesman problem written in C
"main" will output the shortest path, distance, and cpu_time in json format
"""
def tsp_c(request):
    query_string = request.GET.urlencode()
    decoded_string = unquote(query_string)
    point_strings = decoded_string.split('&')
    
    points = []
    for point_str in point_strings:
        x, y = point_str.strip('()=').split(',')
        points.append((int(x), int(y)))
    
    arguments = [] 
    for p in points:
        arguments += [str(p[0]) + "," + str(p[1])]

    c_program_path = "tsp_c/main"
    command = [c_program_path] + arguments
    try:
        result = subprocess.run(command, capture_output=True, text=True, check=True)
        output = result.stdout
        context = ast.literal_eval(output)
        return JsonResponse(context)
    except subprocess.CalledProcessError as e:
        print(f"Enter running C program: {e}")
        return None



