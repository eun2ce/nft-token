# eospet

## Build

```
$ git submodule update --init --recursive
$ ./build.sh
```

## Deploy

```
$ cleos set contract eospet build/eospet/. -p eospet
```

## Usage

```
$ cleos push action eospet createpet '["eospet", "eun2cepet"]' -p eospet
```

## Result

```
{
  "rows": [{
      "id": "10780039778061876128",
      "owner": "eospet",
      "petname": "eun2cepet",
      "type": 0,
      "created_at": "2019-07-09T02:59:57",
      "activated": 0
    }
  ],
  "more": false
}
```
