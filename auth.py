# -*- coding: utf-8 -*-

import time
import base64
import requests
import json
import os


class Auth:

    def __init__(self, client_id, secret, redirect_uri, id = "1", refresh_token="", key=""):
        self._token = ""
        self.token_type = ""
        self.id = id
        self.token_expiry_time = time.time()
        self.code = key
        self.redirect_uri = redirect_uri
        self.client_id = client_id
        self.client_secret = secret
        self.refresh_token_ = refresh_token

    def __enter__(self):
        if self.refresh_token_ == "":
            try:
                self.request_token()
            except Exception:
                print("You need to generate access key")
                os.startfile(AUTH_URL)
                exit(991)
        return self

    def __exit__(self, exc_type, exc_val, exc_tb):
        print('__exit__ called')
        self.save_refresh_token()

    # def load_refresh_token(self):
    #     with open("data/keys.json") as f:  # FIXME
    #         csv_reader = csv.DictReader(f, fieldnames=["id", "token"])
    #         for row in csv_reader:
    #             self.refresh_token_, self.id = row
    #             break
    #
    def save_refresh_token(self):
        pass
    #     with open("data/keys.json", "r+") as f:
    #         pos = f.read().find("]") + 1
    #         f.seek(pos)
    #         record = {self.id: self.refresh_token_}
    #         json_record = json.dumps(record)
    #         f.write(",\n" + json_record + "\n]\n}")

    def request_token(self):
        r = requests.post("https://accounts.spotify.com/api/token",
                          data=self.request_payload,
                          headers=self.authorization_header)
        r.raise_for_status()
        parsed_req = json.loads(r.text)
        self.token_expiry_time = time.time() + parsed_req["expires_in"]
        self.refresh_token_ = parsed_req["refresh_token"]
        self.token_type = parsed_req["token_type"]
        self.token = parsed_req["access_token"]
        
    def refresh_token(self):
        r = requests.post("https://accounts.spotify.com/api/token",
                          data=self.refresh_payload,
                          headers=self.authorization_header)
        r.raise_for_status()
        parsed_req = json.loads(r.text)
        self.token_expiry_time = time.time() + parsed_req["expires_in"]
        self.token_type = parsed_req["token_type"]
        self.token = parsed_req["access_token"]
        
    def is_expired(self):
        if self.token_expiry_time - time.time() < 15:
            return True
        return False
    
    @property
    def token(self):
        if self.is_expired():
            self.refresh_token()
        return self._token
    
    @token.setter
    def token(self, token):
        self._token = token

    @property
    def token_header(self):
        return {"Authorization": b"Bearer " + bytes(self.token, 'utf-8')}

    @property
    def request_payload(self):
        return{"grant_type":"authorization_code",
               "code":self.code,
               "redirect_uri":self.redirect_uri}

    @property
    def refresh_payload(self):
        return {"grant_type":"refresh_token",
                "refresh_token":self.refresh_token_}
    
    @property
    def authorization_header(self):
        return {"Authorization":\
                (b"Basic " + base64.b64encode(bytes(self.client_id+":"+self.client_secret, 'utf-8')))}
