# python3
# Please install OpenAI SDK first：`pip3 install openai`
import sys
import openai
import argparse
parser = argparse.ArgumentParser(description='deepseek api')
parser.add_argument('arg1', help='key')
parser.add_argument('arg2', help='base url')
parser.add_argument('arg3', help='发送内容')
# 解析命令行参数
args = parser.parse_args()
mark_str="|MARK|"

def print_partial_or_complete_response(key,baseurl,question):
    client = openai.OpenAI(api_key=key, base_url=baseurl)
    messages=[
          {"role": "system", "content": ""},
    ]

    result_list = question.split(mark_str)
    for i in range(0,len(result_list)):
        parts = result_list[i].split(":", 1)
        parts_key = parts[0] if parts else ""  
        parts_value = parts[1] if len(parts) > 1 else ""
        if (len(parts_key) != 0) and (len(parts_value) != 0):
            messages.append({"role": parts_key, "content": parts_value})
    response = client.chat.completions.create(
        model="deepseek-chat",
        messages=messages
    )
    
    data =response.choices[0].message.content
    encoded_data=data.encode('utf-8',errors='ignore')
    sys.stdout.buffer.write(encoded_data)
    sys.stdout.buffer.flush()
    
if __name__ == "__main__":
    print_partial_or_complete_response(args.arg1,args.arg2,args.arg3)
