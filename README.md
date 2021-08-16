---
title: SignPlugin
description: Sign data, login and verify signature.
---
<!--
# license: Licensed to the Apache Software Foundation (ASF) under one
#         or more contributor license agreements.  See the NOTICE file
#         distributed with this work for additional information
#         regarding copyright ownership.  The ASF licenses this file
#         to you under the Apache License, Version 2.0 (the
#         "License"); you may not use this file except in compliance
#         with the License.  You may obtain a copy of the License at
#
#           http://www.apache.org/licenses/LICENSE-2.0
#
#         Unless required by applicable law or agreed to in writing,
#         software distributed under the License is distributed on an
#         "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
#         KIND, either express or implied.  See the License for the
#         specific language governing permissions and limitations
#         under the License.
-->

# neptune-sign-plugin

This plugin implements a data signing API allowing to login and verify signature.

## Installation

    cordova plugin add neptune-sign-plugin

## Supported Platforms

- Windows*

## List of Errors raised by plugin
When an error is thrown, one of these messages will be used:

| ERRORS                            						|
|-------------------------------------------------------------------------------|
|    Unable to sign data. No result from method call            		|
|    Unable to sign data. Inner exception on sign data operation        	|
|    Unable to login. No result from method call                		|
|    Unable to login. Inner exception on login operation                	|
|    Unable to verify signature. No result from method call     		|
|    Unable to verify signature. Inner exception on verify signature operation	|

## Signing Data: Signing data sample <a name="signdata"></a>

The File plugin allows you to sign data. On success it creates 'signed.sgn' file with data signature. 
The code snippets in this section demonstrate this task:

```js

cordova.plugins.SignPlugin.signPIV(success, errorstop, [signer, datatosign, true]);

```

## Login: Login sample <a name="login"></a>

The File plugin allows you to sign data. On success it creates 'login.sgn' file.
The code snippets in this section demonstrate this task:

```js

cordova.plugins.SignPlugin.loginPIV(success, errorstop, [signer]);

```

## Verify Signature: Verify Signaturesample <a name="verify"></a>

The File plugin allows you to verify signed data. On success it creates 'result.vrf' file with 'true' or 'false' as result inside.
The code snippets in this section demonstrate this task:

```js

cordova.plugins.SignPlugin.verifyPIV(success, errorstop, [signer, signeddata, signature]);

```

