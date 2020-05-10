import sys
import subprocess
import requests
import re
import pickle
import os

def download_testcase(contest, problem):
    os.makedirs('./cache', exist_ok=True)

    session = requests.session()
    load_cookies(session)

    url='https://atcoder.jp/contests/'+contest+'/tasks/'+contest+'_'+problem
    response=requests.get(url)

    if 'login' in response.url:
        response=login(session, response)
        if response == None:
            return None

    if response.status_code!=200:
        print('#'*20)
        print('page access error '+str(response.status_code))
        print('#'*20)
        return None

    save_cookie(session)

    input_list = re.findall('入力例[\s\S]*?<pre>([\s\S]*?)</pre>', response.text)
    for i in range(len(input_list)):
        input_list[i]=input_list[i].replace('\r','')

    output_list = re.findall('出力例[\s\S]*?<pre>([\s\S]*?)</pre>', response.text)
    for i in range(len(output_list)):
        output_list[i]=output_list[i].replace('\r','')
    
    test_case=[]
    for i in range(len(input_list)):
        test_case.append((input_list[i], output_list[i]))

    return test_case

def get_testcase(contest, problem):
    testcase_path = 'cache/{0}_{1}.pickle'.format(contest, problem)

    if os.path.isfile(testcase_path):
        print('loading test cases..')
        with open(testcase_path, mode='rb') as f:
            test_case = pickle.load(f)
    else:
        print('downloading test cases..')
        test_case = download_testcase(contest, problem)
        with open(testcase_path, mode='wb') as f:
            pickle.dump(test_case, f)
        
    return test_case

def load_cookies(session):
    cookies_path = 'cache/cookies.pickle'
    if os.path.isfile(cookies_path):
        with open(cookies_path, mode='rb') as f:
            cookies = pickle.load(f)
            session.cookies.update(cookies)

def save_cookie(session):
    cookies_path = 'cache/cookies.pickle'
    with open(cookies_path, 'wb') as f:
        pickle.dump(session.cookies, f)

def login(session, response):
    m = re.search(r'value=\"(.*?)\"', response.text)
    csrf_token = m.group(1)

    print('>>>input username')
    username=input()
    print('>>>input password')
    password=input()

    login_data = {
        'csrf_token':csrf_token,
        'username':username,
        'password':password,
    }
    response=session.post(response.url, data=login_data)

    if response.status_code!=200:
        print('login faied.')
        return None

    print('login succeed.')
    return response

def main():
    if len(sys.argv) < 3:
        print('usage: test.py contest_code probrem_name')
        print('example: test.py abc123 a')
        return
    print('build..')

    res = subprocess.run(['g++', '-std=gnu++1y', '-O2', 'main.cpp'])
    if res.returncode == 1:
        print('#'*20)
        print('result: CE')
        print('#'*20)
        return
    print('ok')

    test_case_list=get_testcase(sys.argv[1], sys.argv[2])
    if test_case_list==None:
        return 
    print('ok')

    results=[]
    for i, test_case in enumerate(test_case_list):
        print('>>> test case', i, '..')
        try:
            res = subprocess.run(['./a.out'], stdout=subprocess.PIPE,
                        input=test_case[0].encode('utf8'), timeout=5)
        except subprocess.TimeoutExpired as e:
            print('time exceeded')
            results.append('TLE')
        except subprocess.CalledProcessError as e:
            print('process error')
            results.append('RE')
        else:
            if res.stdout.decode('utf-8') == test_case[1]:
                print('ok')
                results.append('AC')
            else:
                print('test case input >>>')
                print(test_case[0])
                print('test case output >>>')
                print(test_case[1])
                print('process output >>>')
                print(res.stdout.decode('utf-8'))
                results.append('WA')

    print('#'*20)
    print('result:')
    for i, result in enumerate(results):
        print('testcase',i,result)
    print('#'*20)

if __name__=='__main__':
    main()
    
